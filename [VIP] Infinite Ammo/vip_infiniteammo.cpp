#include <stdio.h>
#include "vip_infiniteammo.h"
#include "schemasystem/schemasystem.h"

vip_infiniteammo g_vip_infiniteammo;

IVIPApi* g_pVIPCore;
IUtilsApi* g_pUtils;

CCSGameRules* g_pGameRules = nullptr;

IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;
CGlobalVars* g_pGlobalVars = nullptr;

struct AmmoPack
{
	std::string sName;
	int iDefault;
	std::map<std::string, int> weaponOverrides;
};

static std::map<std::string, AmmoPack> g_Packs;

struct TrackedWeapon
{
	CHandle<CBasePlayerWeapon> hWeapon;
	int iExpectedReserve;
};

struct PlayerAmmoState
{
	TrackedWeapon weapons[10];
	int iCount;
	bool bEnabled;
};

static PlayerAmmoState g_State[64];

PLUGIN_EXPOSE(vip_infiniteammo, g_vip_infiniteammo);

void LoadConfig()
{
	g_Packs.clear();

	KeyValues* kv = new KeyValues("InfiniteReserveAmmo");
	const char* pszPath = "addons/configs/vip/vip_infiniteammo.ini";

	if (!kv->LoadFromFile(g_pFullFileSystem, pszPath))
	{
		g_pUtils->ErrorLog("[%s] Failed to load %s", g_PLAPI->GetLogTag(), pszPath);
		delete kv;
		return;
	}

	FOR_EACH_SUBKEY(kv, pPackKey)
	{
		AmmoPack pack;
		pack.sName = pPackKey->GetName();
		pack.iDefault = 0;

		FOR_EACH_VALUE(pPackKey, pValue)
		{
			const char* szName = pValue->GetName();
			int iVal = pValue->GetInt(nullptr, 0);

			if (!strcmp(szName, "default"))
				pack.iDefault = iVal;
			else
				pack.weaponOverrides[std::string(szName)] = iVal;
		}

		if (pack.iDefault > 0 || !pack.weaponOverrides.empty())
			g_Packs[pack.sName] = pack;
	}

	delete kv;
	ConColorMsg(Color(0, 255, 0, 255), "[VIP-InfiniteAmmo] Loaded %d pack(s)\n", (int)g_Packs.size());
}

int GetTargetReserve(const AmmoPack& pack, const char* szWeaponName)
{
	if (!szWeaponName || !szWeaponName[0]) return pack.iDefault;

	auto it = pack.weaponOverrides.find(std::string(szWeaponName));
	if (it != pack.weaponOverrides.end())
		return it->second;

	return pack.iDefault;
}

const AmmoPack* GetPlayerPack(int iSlot)
{
	if (!g_pVIPCore->VIP_IsClientVIP(iSlot)) return nullptr;

	const char* szPackName = g_pVIPCore->VIP_GetClientFeatureString(iSlot, "InfiniteReserveAmmo");
	if (!szPackName || !szPackName[0]) return nullptr;

	auto it = g_Packs.find(std::string(szPackName));
	if (it != g_Packs.end())
		return &it->second;

	return nullptr;
}

bool IsFirearm(CBasePlayerWeapon* pWeapon)
{
	if (!pWeapon) return false;
	CCSWeaponBase* pWeaponBase = static_cast<CCSWeaponBase*>(pWeapon);
	if (!pWeaponBase) return false;
	CCSWeaponBaseVData* pVData = pWeaponBase->GetWeaponVData();
	if (!pVData) return false;
	return pVData->m_iMaxClip1() > 0;
}

int FindOrCreateSlot(int iPlayerSlot, CBasePlayerWeapon* pWeapon)
{
	PlayerAmmoState& state = g_State[iPlayerSlot];

	for (int i = 0; i < state.iCount; i++)
	{
		if (state.weapons[i].hWeapon.Get() == pWeapon)
			return i;
	}

	if (state.iCount < 10)
	{
		int idx = state.iCount;
		state.weapons[idx].hWeapon = CHandle<CBasePlayerWeapon>(pWeapon);
		state.weapons[idx].iExpectedReserve = -1;
		state.iCount++;
		return idx;
	}

	return -1;
}

void ProcessPlayerWeapons(int iSlot)
{
	if (!g_State[iSlot].bEnabled) return;

	const AmmoPack* pPack = GetPlayerPack(iSlot);
	if (!pPack) return;

	CCSPlayerController* pController = CCSPlayerController::FromSlot(iSlot);
	if (!pController) return;

	CCSPlayerPawn* pPawn = pController->GetPlayerPawn();
	if (!pPawn || !pPawn->IsAlive()) return;

	CPlayer_WeaponServices* pWeaponServices = pPawn->m_pWeaponServices();
	if (!pWeaponServices) return;

	CUtlVector<CHandle<CBasePlayerWeapon>>* pMyWeapons = pWeaponServices->m_hMyWeapons();
	if (!pMyWeapons) return;

	for (int i = 0; i < pMyWeapons->Count(); i++)
	{
		CBasePlayerWeapon* pWeapon = (*pMyWeapons)[i].Get();
		if (!pWeapon) continue;
		if (!IsFirearm(pWeapon)) continue;

		const char* szWeaponName = pWeapon->GetClassname();
		int iTargetReserve = GetTargetReserve(*pPack, szWeaponName);
		if (iTargetReserve <= 0) continue;

		int iSlotIdx = FindOrCreateSlot(iSlot, pWeapon);
		if (iSlotIdx < 0) continue;

		TrackedWeapon& tracked = g_State[iSlot].weapons[iSlotIdx];
		int iCurrentReserve = pWeapon->m_pReserveAmmo()[0];

		if (iCurrentReserve > iTargetReserve)
		{
			pWeapon->m_pReserveAmmo()[0] = iTargetReserve;
			g_pUtils->SetStateChanged(pWeapon, "CBasePlayerWeapon", "m_pReserveAmmo");
			tracked.iExpectedReserve = iTargetReserve;
			continue;
		}

		if (tracked.iExpectedReserve < 0)
		{
			pWeapon->m_pReserveAmmo()[0] = iTargetReserve;
			g_pUtils->SetStateChanged(pWeapon, "CBasePlayerWeapon", "m_pReserveAmmo");
			tracked.iExpectedReserve = iTargetReserve;
			continue;
		}

		if (iCurrentReserve == tracked.iExpectedReserve - 1)
		{
			tracked.iExpectedReserve = iCurrentReserve;
			continue;
		}

		if (iCurrentReserve < tracked.iExpectedReserve - 1)
		{
			int iRestored = tracked.iExpectedReserve - 1;
			if (iRestored < 0) iRestored = 0;

			pWeapon->m_pReserveAmmo()[0] = iRestored;
			g_pUtils->SetStateChanged(pWeapon, "CBasePlayerWeapon", "m_pReserveAmmo");
			tracked.iExpectedReserve = iRestored;
			continue;
		}

		if (iCurrentReserve != tracked.iExpectedReserve)
		{
			tracked.iExpectedReserve = iCurrentReserve;
		}
	}
}

float InfiniteAmmoTimer()
{
	for (int i = 0; i < 64; i++)
	{
		ProcessPlayerWeapons(i);
	}

	return 0.1f;
}

CGameEntitySystem* GameEntitySystem()
{
	return g_pUtils->GetCGameEntitySystem();
}

void ResetPlayerState(int iSlot)
{
	g_State[iSlot].iCount = 0;
	g_State[iSlot].bEnabled = true;
	for (int w = 0; w < 10; w++)
	{
		g_State[iSlot].weapons[w].hWeapon = CHandle<CBasePlayerWeapon>();
		g_State[iSlot].weapons[w].iExpectedReserve = -1;
	}
}

void OnStartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pGameEntitySystem;
	g_pGlobalVars = g_pUtils->GetCGlobalVars();

	LoadConfig();

	g_pUtils->CreateTimer(0.1f, InfiniteAmmoTimer);
}

void GetGameRules()
{
	g_pGameRules = g_pUtils->GetCCSGameRules();
}

void OnClientLoad(int iSlot, bool bIsVIP)
{
	ResetPlayerState(iSlot);
}

void OnClientDisconnect(int iSlot, bool bIsVIP)
{
	ResetPlayerState(iSlot);
}

void OnPlayerSpawn(int iSlot, int iTeam, bool bIsVIP)
{
	ResetPlayerState(iSlot);

	if (!bIsVIP) return;

	g_pUtils->NextFrame([iSlot]()
	{
		ProcessPlayerWeapons(iSlot);

		g_pUtils->NextFrame([iSlot]()
		{
			ProcessPlayerWeapons(iSlot);
		});
	});
}

bool OnToggleInfiniteAmmo(int iSlot, const char* szFeature, VIP_ToggleState eOldStatus, VIP_ToggleState& eNewStatus)
{
	g_State[iSlot].bEnabled = (eNewStatus == ENABLED);
	return false;
}

std::string OnDisplayPack(int iSlot, const char* szFeature)
{
	const char* szPack = g_pVIPCore->VIP_GetClientFeatureString(iSlot, "InfiniteReserveAmmo");
	char szDisplay[128];

	if (szPack && szPack[0])
		g_SMAPI->Format(szDisplay, sizeof(szDisplay), "%s [%s]", g_pVIPCore->VIP_GetTranslate(szFeature), szPack);
	else
		g_SMAPI->Format(szDisplay, sizeof(szDisplay), "%s", g_pVIPCore->VIP_GetTranslate(szFeature));

	return std::string(szDisplay);
}

bool vip_infiniteammo::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
	g_SMAPI->AddListener(this, this);

	for (int i = 0; i < 64; i++)
		ResetPlayerState(i);

	return true;
}

bool vip_infiniteammo::Unload(char* error, size_t maxlen)
{
	g_pVIPCore = nullptr;
	g_pUtils = nullptr;
	return true;
}

void vip_infiniteammo::AllPluginsLoaded()
{
	int ret;
	g_pUtils = (IUtilsApi*)g_SMAPI->MetaFactory(Utils_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED)
	{
		char error[64];
		V_strncpy(error, "Failed to lookup utils api. Aborting", 64);
		ConColorMsg(Color(255, 0, 0, 255), "[%s] %s\n", GetLogTag(), error);
		std::string sBuffer = "meta unload " + std::to_string(g_PLID);
		engine->ServerCommand(sBuffer.c_str());
		return;
	}

	g_pVIPCore = (IVIPApi*)g_SMAPI->MetaFactory(VIP_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED)
	{
		g_pUtils->ErrorLog("[%s] Failed to lookup vip core. Aborting", GetLogTag());
		std::string sBuffer = "meta unload " + std::to_string(g_PLID);
		engine->ServerCommand(sBuffer.c_str());
		return;
	}

	g_pUtils->StartupServer(g_PLID, OnStartupServer);
	g_pUtils->OnGetGameRules(g_PLID, GetGameRules);

	g_pVIPCore->VIP_RegisterFeature("InfiniteReserveAmmo", VIP_STRING, TOGGLABLE,
		nullptr, OnToggleInfiniteAmmo, OnDisplayPack);

	g_pVIPCore->VIP_OnClientLoaded(OnClientLoad);
	g_pVIPCore->VIP_OnClientDisconnect(OnClientDisconnect);
	g_pVIPCore->VIP_OnPlayerSpawn(OnPlayerSpawn);
}

///////////////////////////////////////
const char* vip_infiniteammo::GetLicense()
{
	return "Public";
}

const char* vip_infiniteammo::GetVersion()
{
	return "1.0";
}

const char* vip_infiniteammo::GetDate()
{
	return __DATE__;
}

const char* vip_infiniteammo::GetLogTag()
{
	return "[VIP-InfiniteAmmo]";
}

const char* vip_infiniteammo::GetAuthor()
{
	return "_ded_cookies";
}

const char* vip_infiniteammo::GetDescription()
{
	return "VIP Infinite Reserve Ammo";
}

const char* vip_infiniteammo::GetName()
{
	return "[VIP] Infinite Reserve Ammo";
}

const char* vip_infiniteammo::GetURL()
{
	return "https://api.onlypublic.net/";
}
