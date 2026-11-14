#include <stdio.h>
#include "vip_reserved_slots.h"
#include "metamod_oslink.h"
#include "schemasystem/schemasystem.h"
#include "filesystem.h"
#include <steam/steam_gameserver.h>
#include <vector>
#include <string>
#include <random>
#include <cstring>
#include <cstdlib>

vip_reserved_slots g_reserved_slots;
PLUGIN_EXPOSE(vip_reserved_slots, g_reserved_slots);

IVEngineServer2*   engine              = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem*     g_pEntitySystem     = nullptr;
CGlobalVars*       gpGlobals           = nullptr;

IUtilsApi*   g_pUtils      = nullptr;
IPlayersApi* g_pPlayersApi = nullptr;
IVIPApi*     g_pVIP        = nullptr;

static std::mt19937 g_rng(std::random_device{}());

struct ReservedSlotsConfig
{
	int  publicSlots  = 0;
	int  reserveSlots = 0;

	int  kickReasonId = 135;
	bool kickRandom   = false;
	bool evictNonVip  = false;

	int  hideSlots    = -1;

	std::vector<std::string> allowedGroups;
	int effectivePublic = 0;
	int effectiveHide   = 0;
};

ReservedSlotsConfig g_ReservedCfg;
const char* g_szReservedConfigPath = "addons/configs/vip/vip_reserved_slots.ini";

static void LoadReservedSlotsConfig();
static bool HasReserveAccess(int iSlot);
static int  CountNonReservePlayers(int excludeSlot);
static int  FindNonReservePlayerToKick(int avoidSlot);
static void KickClientForReserve(int iSlot, int iReasonId);
static void OnVIPClientLoaded(int iSlot, bool bIsVIP);

void StartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem     = g_pUtils->GetCEntitySystem();
	gpGlobals           = g_pUtils->GetCGlobalVars();

	LoadReservedSlotsConfig();
}

bool vip_reserved_slots::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_CURRENT(GetEngineFactory,     g_pCVar,           ICvar,             CVAR_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
	GET_V_IFACE_ANY    (GetEngineFactory,     g_pSchemaSystem,   ISchemaSystem,     SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory,     engine,            IVEngineServer2,   SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem,       FILESYSTEM_INTERFACE_VERSION);

	g_SMAPI->AddListener(this, this);

	return true;
}

bool vip_reserved_slots::Unload(char* error, size_t maxlen)
{
	return true;
}

static inline std::string MakeMetaUnloadCommand(PluginId id)
{
	return std::string("meta unload ") + std::to_string(id);
}

static void ApplyHideSlots()
{
	if (g_ReservedCfg.effectiveHide <= 0) return;
	if (ISteamGameServer* p = SteamGameServer())
		p->SetMaxPlayerCount(g_ReservedCfg.effectiveHide);
}

void vip_reserved_slots::AllPluginsLoaded()
{
	int ret;

	g_pUtils = (IUtilsApi*)g_SMAPI->MetaFactory(UTILS_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED || !g_pUtils)
	{
		ConColorMsg(Color(255, 0, 0, 255), "[VRS] Missing Utils\n");
		if (engine) engine->ServerCommand(MakeMetaUnloadCommand(g_PLID).c_str());
		return;
	}

	g_pPlayersApi = (IPlayersApi*)g_SMAPI->MetaFactory(PLAYERS_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED || !g_pPlayersApi)
	{
		g_pUtils->ErrorLog("[VRS] Missing Players");
		engine->ServerCommand(MakeMetaUnloadCommand(g_PLID).c_str());
		return;
	}

	g_pVIP = (IVIPApi*)g_SMAPI->MetaFactory(VIP_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED || !g_pVIP)
	{
		g_pUtils->ErrorLog("[VRS] Missing VIP API");
		engine->ServerCommand(MakeMetaUnloadCommand(g_PLID).c_str());
		return;
	}

	g_pVIP->VIP_OnClientLoaded(OnVIPClientLoaded);
	g_pUtils->StartupServer(g_PLID, StartupServer);

	g_pUtils->CreateTimer(10.0f, []() -> float {
		ApplyHideSlots();
		return 10.0f;
	});
}

static void ParseGroupList(const char* src, std::vector<std::string>& out)
{
	out.clear();
	if (!src || !*src) return;
	std::string s = src;
	size_t st = 0;
	while (true)
	{
		size_t p = s.find(';', st);
		std::string c = (p == std::string::npos) ? s.substr(st) : s.substr(st, p - st);
		while (!c.empty() && (c.front() == ' ' || c.front() == '\t')) c.erase(c.begin());
		while (!c.empty() && (c.back()  == ' ' || c.back()  == '\t')) c.pop_back();
		if (!c.empty()) out.push_back(c);
		if (p == std::string::npos) break;
		st = p + 1;
	}
}

static void LoadReservedSlotsConfig()
{
	if (!g_pFullFileSystem) return;

	g_ReservedCfg = {};

	int maxClients = gpGlobals ? gpGlobals->maxClients : 0;

	KeyValues* pKv = new KeyValues("ReservedSlots");
	if (!pKv->LoadFromFile(g_pFullFileSystem, g_szReservedConfigPath))
	{
		if (g_pUtils)
			g_pUtils->ErrorLog("[VRS] Failed to load %s, using defaults", g_szReservedConfigPath);
		pKv->deleteThis();
	}
	else
	{
		g_ReservedCfg.publicSlots  = pKv->GetInt("public_slots",   0);
		g_ReservedCfg.reserveSlots = pKv->GetInt("reserve_slots",  0);
		g_ReservedCfg.kickReasonId = pKv->GetInt("kick_reason_id", 135);
		g_ReservedCfg.kickRandom   = pKv->GetInt("kick_random",  0) != 0;
		g_ReservedCfg.evictNonVip  = pKv->GetInt("evict_nonvip", 0) != 0;
		g_ReservedCfg.hideSlots    = pKv->GetInt("hide_slots",  -1);

		const char* groups = pKv->GetString("vip_groups", "");
		ParseGroupList(groups, g_ReservedCfg.allowedGroups);

		pKv->deleteThis();
	}

	int eff = 0;
	if (g_ReservedCfg.publicSlots > 0)
	{
		eff = g_ReservedCfg.publicSlots;
	}
	else if (g_ReservedCfg.reserveSlots > 0 && maxClients > 0)
	{
		eff = maxClients - g_ReservedCfg.reserveSlots;
	}
	else if (maxClients > 0)
	{
		eff = (maxClients > 2) ? (maxClients - 2) : maxClients;
	}

	if (eff < 0) eff = 0;
	if (maxClients > 0 && eff > maxClients) eff = maxClients;

	g_ReservedCfg.effectivePublic = eff;

	if (g_ReservedCfg.kickReasonId < 0)
		g_ReservedCfg.kickReasonId = 135;

	if (g_ReservedCfg.hideSlots < 0)
		g_ReservedCfg.effectiveHide = g_ReservedCfg.effectivePublic;
	else
		g_ReservedCfg.effectiveHide = g_ReservedCfg.hideSlots;

	if (g_ReservedCfg.effectiveHide > 0)
	{
		ApplyHideSlots();
		Msg("[VRS] public=%d reserve=%d browser_slots=%d\n",
			g_ReservedCfg.effectivePublic,
			maxClients > 0 ? (maxClients - g_ReservedCfg.effectivePublic) : 0,
			g_ReservedCfg.effectiveHide);
	}
}

static bool HasReserveAccess(int iSlot)
{
	if (!g_pVIP) return false;
	if (!g_pVIP->VIP_IsClientVIP(iSlot)) return false;

	if (g_ReservedCfg.allowedGroups.empty()) return true;

	const char* grp = g_pVIP->VIP_GetClientVIPGroup(iSlot);
	if (!grp || !*grp) return false;
	for (auto& g : g_ReservedCfg.allowedGroups)
		if (g == grp) return true;
	return false;
}

static int CountNonReservePlayers(int excludeSlot = -1)
{
	if (!g_pPlayersApi || !gpGlobals) return 0;
	int iCount = 0;
	for (int i = 0; i < gpGlobals->maxClients; ++i)
	{
		if (i == excludeSlot) continue;
		if (!g_pPlayersApi->IsConnected(i) || g_pPlayersApi->IsFakeClient(i)) continue;
		if (HasReserveAccess(i)) continue;
		iCount++;
	}
	return iCount;
}

static int CountTotalRealPlayers()
{
	if (!g_pPlayersApi || !gpGlobals) return 0;
	int iCount = 0;
	for (int i = 0; i < gpGlobals->maxClients; ++i)
	{
		if (!g_pPlayersApi->IsConnected(i) || g_pPlayersApi->IsFakeClient(i)) continue;
		iCount++;
	}
	return iCount;
}

static int FindNonReservePlayerToKick(int avoidSlot)
{
	if (!g_pPlayersApi || !gpGlobals) return -1;

	std::vector<int> candidates;
	for (int i = 0; i < gpGlobals->maxClients; ++i)
	{
		if (i == avoidSlot) continue;
		if (!g_pPlayersApi->IsConnected(i) || g_pPlayersApi->IsFakeClient(i)) continue;
		if (HasReserveAccess(i)) continue;
		candidates.push_back(i);
	}
	if (candidates.empty()) return -1;
	if (g_ReservedCfg.kickRandom)
	{
		std::uniform_int_distribution<size_t> dist(0, candidates.size() - 1);
		return candidates[dist(g_rng)];
	}
	return candidates.front();
}

static void KickClientForReserve(int iSlot, int iReasonId)
{
	if (!engine || !g_pPlayersApi) return;
	if (!g_pPlayersApi->IsConnected(iSlot)) return;
	engine->DisconnectClient(CPlayerSlot(iSlot), static_cast<ENetworkDisconnectionReason>(iReasonId));
}

static void OnVIPClientLoaded(int iSlot, bool bIsVIP)
{
	if (!g_pPlayersApi || !g_pVIP || !gpGlobals) return;
	if (g_pPlayersApi->IsFakeClient(iSlot)) return;
	if (!g_pPlayersApi->IsConnected(iSlot)) return;

	const int iMaxClients = gpGlobals->maxClients;
	if (iMaxClients <= 0) return;

	const bool bHasReserve       = bIsVIP && HasReserveAccess(iSlot);
	const int  iEffectivePub     = g_ReservedCfg.effectivePublic;
	const int  iOthersNonReserve = CountNonReservePlayers(iSlot);

	if (!bHasReserve)
	{
		if (iOthersNonReserve >= iEffectivePub)
		{
			Msg("[VRS] reject non-vip slot=%d (others_non_vip=%d >= public_limit=%d)\n",
				iSlot, iOthersNonReserve, iEffectivePub);
			KickClientForReserve(iSlot, g_ReservedCfg.kickReasonId);
		}
		return;
	}

	if (g_ReservedCfg.evictNonVip)
	{
		int total = CountTotalRealPlayers();
		if (total >= iMaxClients && iOthersNonReserve > 0)
		{
			int iTarget = FindNonReservePlayerToKick(iSlot);
			if (iTarget >= 0)
			{
				Msg("[VRS] evict non-vip slot=%d to make room for VIP slot=%d (total=%d/%d)\n",
					iTarget, iSlot, total, iMaxClients);
				KickClientForReserve(iTarget, g_ReservedCfg.kickReasonId);
			}
		}
	}
}

const char *vip_reserved_slots::GetLicense()
{
    return "Public";
}

const char *vip_reserved_slots::GetVersion()
{
    return "1.0.1";
}

const char *vip_reserved_slots::GetDate()
{
    return __DATE__;
}

const char *vip_reserved_slots::GetLogTag()
{
    return "[VRS]";
}

const char *vip_reserved_slots::GetAuthor()
{
    return "_ded_cookies";
}

const char *vip_reserved_slots::GetDescription()
{
    return "Reserved slots for VIP";
}

const char *vip_reserved_slots::GetName()
{
    return "[VIP] Reserved slots";
}

const char *vip_reserved_slots::GetURL()
{
    return "https://api.onlypublic.net/";
}