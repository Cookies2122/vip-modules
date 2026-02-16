#include <stdio.h>
#include "vip_regenammo.h"
#include "schemasystem/schemasystem.h"

vip_regenammo g_vip_regenammo;

IVIPApi* g_pVIPCore;
IUtilsApi* g_pUtils;

CCSGameRules* g_pGameRules = nullptr;

IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;
CGlobalVars* g_pGlobalVars = nullptr;

struct WeaponInBeltInfo {
	CHandle<CBasePlayerWeapon> hWeapon;
	float fTimeInBelt;
	int iLastKnownClip;
	int iRegenCount;
	int iMaxClip;
	bool bWasActive;
};

struct PlayerRegenInfo {
	WeaponInBeltInfo weapons[5];
	CHandle<CBasePlayerWeapon> hActiveWeapon;
};

PlayerRegenInfo g_RegenInfo[64];

PLUGIN_EXPOSE(vip_regenammo, g_vip_regenammo);

bool vip_regenammo::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
	g_SMAPI->AddListener(this, this);
	
	for (int i = 0; i < 64; i++)
	{
		for (int w = 0; w < 5; w++)
		{
			g_RegenInfo[i].weapons[w].hWeapon = CHandle<CBasePlayerWeapon>();
			g_RegenInfo[i].weapons[w].fTimeInBelt = 0.0f;
			g_RegenInfo[i].weapons[w].iLastKnownClip = 0;
			g_RegenInfo[i].weapons[w].iRegenCount = 0;
			g_RegenInfo[i].weapons[w].iMaxClip = 0;
			g_RegenInfo[i].weapons[w].bWasActive = false;
		}
		g_RegenInfo[i].hActiveWeapon = CHandle<CBasePlayerWeapon>();
	}
	
	return true;
}

bool vip_regenammo::Unload(char *error, size_t maxlen)
{
	if (g_pUtils)
		g_pUtils->ClearAllHooks(g_PLID);
	
	g_pVIPCore = nullptr;
	g_pUtils = nullptr;
	return true;
}

void ClearPlayerData(int iSlot)
{
	if (iSlot < 0 || iSlot >= 64) return;
	
	for (int w = 0; w < 5; w++)
	{
		g_RegenInfo[iSlot].weapons[w].hWeapon = CHandle<CBasePlayerWeapon>();
		g_RegenInfo[iSlot].weapons[w].fTimeInBelt = 0.0f;
		g_RegenInfo[iSlot].weapons[w].iLastKnownClip = 0;
		g_RegenInfo[iSlot].weapons[w].iRegenCount = 0;
		g_RegenInfo[iSlot].weapons[w].iMaxClip = 0;
		g_RegenInfo[iSlot].weapons[w].bWasActive = false;
	}
	g_RegenInfo[iSlot].hActiveWeapon = CHandle<CBasePlayerWeapon>();
}

bool IsValidWeaponForRegen(CBasePlayerWeapon* pWeapon)
{
	if (!pWeapon) return false;
	
	CCSWeaponBase* pWeaponBase = static_cast<CCSWeaponBase*>(pWeapon);
	if (!pWeaponBase) return false;
	
	CCSWeaponBaseVData* pVData = pWeaponBase->GetWeaponVData();
	if (!pVData) return false;
	
	int iMaxClip = pVData->m_iMaxClip1();
	if (iMaxClip <= 0) return false;
	
	return true;
}

int GetWeaponMaxClip(CBasePlayerWeapon* pWeapon)
{
	if (!pWeapon) return 0;
	
	CCSWeaponBase* pWeaponBase = static_cast<CCSWeaponBase*>(pWeapon);
	if (!pWeaponBase) return 0;
	
	CCSWeaponBaseVData* pVData = pWeaponBase->GetWeaponVData();
	if (!pVData) return 0;
	
	return pVData->m_iMaxClip1();
}

void UpdatePlayerWeapons(int iSlot)
{
	CCSPlayerController* pController = CCSPlayerController::FromSlot(iSlot);
	if (!pController) return;
	
	CCSPlayerPawn* pPawn = pController->GetPlayerPawn();
	if (!pPawn || !pPawn->IsAlive()) 
	{
		ClearPlayerData(iSlot);
		return;
	}
	
	CPlayer_WeaponServices* pWeaponServices = pPawn->m_pWeaponServices();
	if (!pWeaponServices) return;
	
	CBasePlayerWeapon* pActiveWeapon = pWeaponServices->m_hActiveWeapon().Get();
	CBasePlayerWeapon* pPrevActiveWeapon = g_RegenInfo[iSlot].hActiveWeapon.Get();
	
	bool bActiveWeaponChanged = (pActiveWeapon != pPrevActiveWeapon);
	g_RegenInfo[iSlot].hActiveWeapon = pWeaponServices->m_hActiveWeapon();
	
	CUtlVector<CHandle<CBasePlayerWeapon>>* pMyWeapons = pWeaponServices->m_hMyWeapons();
	if (!pMyWeapons) return;
	
	float fCurrentTime = g_pGlobalVars->curtime;
	
	for (int w = 0; w < 5; w++)
	{
		CBasePlayerWeapon* pStored = g_RegenInfo[iSlot].weapons[w].hWeapon.Get();
		if (!pStored) continue;
		
		bool bStillExists = false;
		for (int i = 0; i < pMyWeapons->Count(); i++)
		{
			if ((*pMyWeapons)[i].Get() == pStored)
			{
				bStillExists = true;
				break;
			}
		}
		
		if (!bStillExists)
		{
			g_RegenInfo[iSlot].weapons[w].hWeapon = CHandle<CBasePlayerWeapon>();
			g_RegenInfo[iSlot].weapons[w].fTimeInBelt = 0.0f;
			g_RegenInfo[iSlot].weapons[w].iLastKnownClip = 0;
			g_RegenInfo[iSlot].weapons[w].iRegenCount = 0;
			g_RegenInfo[iSlot].weapons[w].iMaxClip = 0;
			g_RegenInfo[iSlot].weapons[w].bWasActive = false;
			continue;
		}
		
		bool bIsActive = (pStored == pActiveWeapon);
		bool bWasActive = g_RegenInfo[iSlot].weapons[w].bWasActive;
		
		if (bIsActive && !bWasActive)
		{
			g_RegenInfo[iSlot].weapons[w].iRegenCount = 0;
		}
		else if (!bIsActive && bWasActive)
		{
			g_RegenInfo[iSlot].weapons[w].fTimeInBelt = fCurrentTime;
		}
		
		g_RegenInfo[iSlot].weapons[w].bWasActive = bIsActive;
	}
	
	for (int i = 0; i < pMyWeapons->Count(); i++)
	{
		CBasePlayerWeapon* pWeapon = (*pMyWeapons)[i].Get();
		if (!pWeapon) continue;
		if (!IsValidWeaponForRegen(pWeapon)) continue;
		
		bool bFound = false;
		for (int w = 0; w < 5; w++)
		{
			CBasePlayerWeapon* pStored = g_RegenInfo[iSlot].weapons[w].hWeapon.Get();
			if (pStored == pWeapon)
			{
				bFound = true;
				break;
			}
		}
		
		if (!bFound)
		{
			for (int w = 0; w < 5; w++)
			{
				CBasePlayerWeapon* pStored = g_RegenInfo[iSlot].weapons[w].hWeapon.Get();
				if (!pStored)
				{
					bool bIsActive = (pWeapon == pActiveWeapon);
					
					g_RegenInfo[iSlot].weapons[w].hWeapon = CHandle<CBasePlayerWeapon>(pWeapon);
					g_RegenInfo[iSlot].weapons[w].fTimeInBelt = bIsActive ? 0.0f : fCurrentTime;
					g_RegenInfo[iSlot].weapons[w].iLastKnownClip = pWeapon->m_iClip1();
					g_RegenInfo[iSlot].weapons[w].iRegenCount = 0;
					g_RegenInfo[iSlot].weapons[w].iMaxClip = GetWeaponMaxClip(pWeapon);
					g_RegenInfo[iSlot].weapons[w].bWasActive = bIsActive;
					break;
				}
			}
		}
	}
}

void RegenWeaponsInBelt(int iSlot)
{
	if (!g_pVIPCore || !g_pVIPCore->VIP_IsClientVIP(iSlot)) return;
	
	float fDelayInBelt = g_pVIPCore->VIP_GetClientFeatureFloat(iSlot, "DelayRegenAmmunition");
	int iRegenAmount = (int)g_pVIPCore->VIP_GetClientFeatureFloat(iSlot, "RegenAmmunition");
	
	if (fDelayInBelt <= 0.0f || iRegenAmount <= 0) return;
	
	CCSPlayerController* pController = CCSPlayerController::FromSlot(iSlot);
	if (!pController) return;
	
	CCSPlayerPawn* pPawn = pController->GetPlayerPawn();
	if (!pPawn || !pPawn->IsAlive()) return;
	
	CPlayer_WeaponServices* pWeaponServices = pPawn->m_pWeaponServices();
	if (!pWeaponServices) return;
	
	float fCurrentTime = g_pGlobalVars->curtime;
	CBasePlayerWeapon* pActiveWeapon = g_RegenInfo[iSlot].hActiveWeapon.Get();
	
	for (int w = 0; w < 5; w++)
	{
		CBasePlayerWeapon* pWeapon = g_RegenInfo[iSlot].weapons[w].hWeapon.Get();
		if (!pWeapon) continue;
		
		if (pWeapon == pActiveWeapon) continue;
		
		if (g_RegenInfo[iSlot].weapons[w].bWasActive) continue;
		
		if (g_RegenInfo[iSlot].weapons[w].fTimeInBelt <= 0.0f) continue;
		
		float fTimeInBelt = fCurrentTime - g_RegenInfo[iSlot].weapons[w].fTimeInBelt;
		
		if (fTimeInBelt < fDelayInBelt) continue;
		
		int iCurrentClip = pWeapon->m_iClip1();
		int iMaxClip = g_RegenInfo[iSlot].weapons[w].iMaxClip;
		
		if (iCurrentClip >= iMaxClip) continue;
		
		int iReserveAmmo = pWeapon->m_pReserveAmmo()[0];
		
		if (iReserveAmmo <= 0) continue;
		
		int iMaxRegens = (iMaxClip * 2) / iRegenAmount;
		if (iMaxRegens < 3) iMaxRegens = 3;
		if (iMaxRegens > 20) iMaxRegens = 20;
		
		if (g_RegenInfo[iSlot].weapons[w].iRegenCount >= iMaxRegens)
		{
			continue;
		}
		
		int iAmmoToAdd = iRegenAmount;
		int iSpaceInClip = iMaxClip - iCurrentClip;
		
		if (iAmmoToAdd > iSpaceInClip)
			iAmmoToAdd = iSpaceInClip;
		
		if (iAmmoToAdd > iReserveAmmo)
			iAmmoToAdd = iReserveAmmo;
		
		int iNewClip = iCurrentClip + iAmmoToAdd;
		int iNewReserve = iReserveAmmo - iAmmoToAdd;
		
		pWeapon->m_iClip1() = iNewClip;
		pWeapon->m_pReserveAmmo()[0] = iNewReserve;
		
		g_pUtils->SetStateChanged(pWeapon, "CBasePlayerWeapon", "m_iClip1");
		g_pUtils->SetStateChanged(pWeapon, "CBasePlayerWeapon", "m_pReserveAmmo");
		
		g_RegenInfo[iSlot].weapons[w].iRegenCount++;
		g_RegenInfo[iSlot].weapons[w].iLastKnownClip = iNewClip;
	}
}

float CheckWeaponsTimer()
{
	if (!g_pVIPCore || !g_pUtils) return 1.0f;
	
	for (int i = 0; i < 64; i++)
	{
		if (!g_pVIPCore->VIP_IsClientVIP(i)) continue;
		
		UpdatePlayerWeapons(i);
		RegenWeaponsInBelt(i);
	}
	
	return 1.0f;
}

CGameEntitySystem* GameEntitySystem()
{
	return g_pUtils->GetCGameEntitySystem();
}

void OnStartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pGameEntitySystem;
	g_pGlobalVars = g_pUtils->GetCGlobalVars();
	
	for (int i = 0; i < 64; i++)
	{
		ClearPlayerData(i);
	}
	
	g_pUtils->CreateTimer(1.0f, CheckWeaponsTimer);
}

void GetGameRules()
{
	g_pGameRules = g_pUtils->GetCCSGameRules();
}

void OnClientLoad(int iSlot, bool bIsVIP)
{
	ClearPlayerData(iSlot);
}

void OnClientDisconnect(int iSlot, bool bIsVIP)
{
	ClearPlayerData(iSlot);
}

void OnPlayerSpawn(int iSlot, int iTeam, bool bIsVIP)
{
	ClearPlayerData(iSlot);
}

std::string OnDisplayDelay(int iSlot, const char* szFeature)
{
	if (!g_pVIPCore) return szFeature;
	
	float fDelay = g_pVIPCore->VIP_GetClientFeatureFloat(iSlot, "DelayRegenAmmunition");
	char szDisplay[128];
	g_SMAPI->Format(szDisplay, sizeof(szDisplay), "%s [%.1f s.]", 
		g_pVIPCore->VIP_GetTranslate(szFeature), fDelay);
	return std::string(szDisplay);
}

void vip_regenammo::AllPluginsLoaded()
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
	
	g_pVIPCore->VIP_RegisterFeature("RegenAmmunition", VIP_INT, HIDE);
	g_pVIPCore->VIP_RegisterFeature("DelayRegenAmmunition", VIP_FLOAT, TOGGLABLE, 
		nullptr, nullptr, OnDisplayDelay);
	
	g_pVIPCore->VIP_OnClientLoaded(OnClientLoad);
	g_pVIPCore->VIP_OnClientDisconnect(OnClientDisconnect);
	g_pVIPCore->VIP_OnPlayerSpawn(OnPlayerSpawn);
}

const char *vip_regenammo::GetLicense()
{
	return "Public";
}

const char *vip_regenammo::GetVersion()
{
	return "1.1";
}

const char *vip_regenammo::GetDate()
{
	return __DATE__;
}

const char *vip_regenammo::GetLogTag()
{
	return "[VIP-RegenAmmo]";
}

const char *vip_regenammo::GetAuthor()
{
	return "_ded_cookies";
}

const char *vip_regenammo::GetDescription()
{
	return "VIP Ammunition Regeneration for weapons in belt";
}

const char *vip_regenammo::GetName()
{
	return "[VIP] Ammo Regen";
}

const char *vip_regenammo::GetURL()
{
	return "https://api.onlypublic.net/";
}
