#include <stdio.h>
#include "vip_respawn.h"
#include "schemasystem/schemasystem.h"

vip_respawn g_vip_respawn;

IVIPApi*    g_pVIPCore = nullptr;
IUtilsApi*  g_pUtils   = nullptr;
IPlayersApi* g_pPlayers = nullptr;

IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem*     g_pEntitySystem     = nullptr;

struct RespawnSettings
{
	int   iMaxRespawns;
	bool  bAutoRespawn;
	float fNoRespawnDelay;
	float fNoAutoRespawnDelay;
	float fRespawnDelay;
	float fAutoRespawnDelay;
	int   iMinPlayers;
	int   iAutoMinPlayers;
	int   iHPAfterRespawn;
	int   iHPAfterAutoRespawn;
	int   iMinAliveMode;
	int   iMinAlive;
};

static RespawnSettings g_Cfg = {
	3, true, 40.0f, 35.0f, 7.0f, 3.0f, 2, 5, 75, 50, 2, 2
};

static int     g_iRespawns[64];
static bool    g_bRespawnReady[64];
static bool    g_bAutoReady[64];
static CTimer* g_pNoRespawnTimer[64]     = { nullptr };
static CTimer* g_pNoAutoTimer[64]        = { nullptr };
static CTimer* g_pRespawnDelayTimer[64]  = { nullptr };
static CTimer* g_pAutoDelayTimer[64]     = { nullptr };

PLUGIN_EXPOSE(vip_respawn, g_vip_respawn);

static void LoadConfig()
{
	const char* szPath = "addons/configs/vip/vip_respawn.ini";

	KeyValues* pKv = new KeyValues("VIP_Respawn");
	if (!pKv->LoadFromFile(g_pFullFileSystem, szPath))
	{
		Warning("[VIP-Respawn++] Config not found at %s, defaults applied.\n", szPath);
		delete pKv;
		return;
	}

	g_Cfg.iMaxRespawns        = pKv->GetInt  ("RespawnEnhanced",        3);
	g_Cfg.bAutoRespawn        = pKv->GetInt  ("AutoRespawn",            1) != 0;
	g_Cfg.fNoRespawnDelay     = pKv->GetFloat("NoRespawnDelay",         40.0f);
	g_Cfg.fNoAutoRespawnDelay = pKv->GetFloat("NoAutoRespawnDelay",     35.0f);
	g_Cfg.fRespawnDelay       = pKv->GetFloat("RespawnDelay",           7.0f);
	g_Cfg.fAutoRespawnDelay   = pKv->GetFloat("AutoRespawnDelay",       3.0f);
	g_Cfg.iMinPlayers         = pKv->GetInt  ("RespawnMinPlayers",      2);
	g_Cfg.iAutoMinPlayers     = pKv->GetInt  ("AutoRespawnMinPlayers",  5);
	g_Cfg.iHPAfterRespawn     = pKv->GetInt  ("HPAfterRespawn",         75);
	g_Cfg.iHPAfterAutoRespawn = pKv->GetInt  ("HPAfterAutoRespawn",     50);
	g_Cfg.iMinAliveMode       = pKv->GetInt  ("MinAliveMode",           2);
	g_Cfg.iMinAlive           = pKv->GetInt  ("MinAlive",               2);

	delete pKv;
}

static void KillTimer(CTimer*& pTimer)
{
	if (pTimer)
	{
		g_pUtils->RemoveTimer(pTimer);
		pTimer = nullptr;
	}
}

static int CountOnlinePlayers()
{
	int n = 0;
	for (int i = 0; i < 64; ++i)
	{
		if (g_pPlayers->IsFakeClient(i))         continue;
		if (!g_pPlayers->IsAuthenticated(i))     continue;
		if (!g_pPlayers->IsInGame(i))            continue;
		if (!g_pPlayers->IsConnected(i))         continue;
		++n;
	}
	return n;
}

static int CountAliveInTeam(int iTeam)
{
	int n = 0;
	for (int i = 0; i < 64; ++i)
	{
		if (g_pPlayers->IsFakeClient(i)) continue;
		if (!g_pPlayers->IsInGame(i))    continue;

		CCSPlayerController* pC = CCSPlayerController::FromSlot(i);
		if (!pC || pC->m_iTeamNum() != iTeam) continue;

		CCSPlayerPawnBase* pP = pC->m_hPlayerPawn();
		if (!pP || pP->m_lifeState() != LIFE_ALIVE) continue;

		++n;
	}
	return n;
}

static bool MinAlivePassed(int iSlot)
{
	if (g_Cfg.iMinAlive <= 0) return true;

	CCSPlayerController* pC = CCSPlayerController::FromSlot(iSlot);
	if (!pC) return false;

	int iTeam = pC->m_iTeamNum();
	if (iTeam < 2) return false;

	int iEnemyTeam = (iTeam == 2) ? 3 : 2;

	switch (g_Cfg.iMinAliveMode)
	{
		case 0: return CountAliveInTeam(iTeam)      > g_Cfg.iMinAlive;
		case 1: return CountAliveInTeam(iEnemyTeam) > g_Cfg.iMinAlive;
		case 2: return CountAliveInTeam(iTeam)      > g_Cfg.iMinAlive
		           && CountAliveInTeam(iEnemyTeam) > g_Cfg.iMinAlive;
	}
	return true;
}

static void Notify(int iSlot, const char* szPhrase)
{
	g_pUtils->PrintToChat(iSlot, "%s %s",
		g_pVIPCore->VIP_GetTranslate("Prefix"),
		g_pVIPCore->VIP_GetTranslate(szPhrase));
}

static void NotifyCount(int iSlot, const char* szPhrase, int iLeft)
{
	char szBuf[128];
	snprintf(szBuf, sizeof(szBuf), g_pVIPCore->VIP_GetTranslate(szPhrase), iLeft);
	g_pUtils->PrintToChat(iSlot, "%s %s",
		g_pVIPCore->VIP_GetTranslate("Prefix"), szBuf);
}

static void DoRespawn(int iSlot, int iHealth)
{
	g_iRespawns[iSlot]++;
	g_pPlayers->Respawn(iSlot);

	CCSPlayerController* pC = CCSPlayerController::FromSlot(iSlot);
	if (!pC) return;

	CCSPlayerPawn* pP = pC->m_hPlayerPawn();
	if (pP && pP->IsAlive() && iHealth > 0)
		pP->m_iHealth() = iHealth;

	NotifyCount(iSlot, "RespawnRemaining", g_Cfg.iMaxRespawns - g_iRespawns[iSlot]);
}

static bool OnRespawnCommand(int iSlot, const char* szContent)
{
	if (!g_pVIPCore->VIP_IsClientVIP(iSlot))                       return false;
	if (!g_pVIPCore->VIP_GetClientFeatureBool(iSlot, "respawn"))   return false;
	if (g_Cfg.iMaxRespawns <= 0)                                   return false;

	if (g_iRespawns[iSlot] >= g_Cfg.iMaxRespawns)
	{
		Notify(iSlot, "LimitRespawn");
		return false;
	}

	CCSPlayerController* pC = CCSPlayerController::FromSlot(iSlot);
	if (!pC) return false;

	CCSPlayerPawnBase* pPawn = pC->m_hPlayerPawn();
	if (!pPawn || pPawn->m_lifeState() == LIFE_ALIVE)
	{
		Notify(iSlot, "YourAlive");
		return false;
	}

	if (pC->m_iTeamNum() < 2)
	{
		Notify(iSlot, "SelectTeam");
		return false;
	}

	if (!g_bRespawnReady[iSlot])
	{
		Notify(iSlot, "RespawnIsNotAvailable");
		return false;
	}

	if (!MinAlivePassed(iSlot))
	{
		Notify(iSlot, "RespawnBlockedMinAlive");
		return false;
	}

	DoRespawn(iSlot, g_Cfg.iHPAfterRespawn);
	return false;
}

static bool OnMenuSelect(int iSlot, const char* /*szFeature*/)
{
	OnRespawnCommand(iSlot, "");
	return false;
}

static std::string OnMenuDisplay(int iSlot, const char* szFeature)
{
	char szBuf[128];
	int iLeft = g_Cfg.iMaxRespawns - g_iRespawns[iSlot];
	g_SMAPI->Format(szBuf, sizeof(szBuf), "%s [%i]",
		g_pVIPCore->VIP_GetTranslate(szFeature), iLeft);
	return std::string(szBuf);
}

static void OnRoundStart(const char*, IGameEvent*, bool)
{
	for (int iSlot = 0; iSlot < 64; ++iSlot)
	{
		KillTimer(g_pNoRespawnTimer[iSlot]);
		KillTimer(g_pNoAutoTimer[iSlot]);
		KillTimer(g_pRespawnDelayTimer[iSlot]);
		KillTimer(g_pAutoDelayTimer[iSlot]);

		g_iRespawns[iSlot]     = 0;
		g_bRespawnReady[iSlot] = true;
		g_bAutoReady[iSlot]    = g_Cfg.bAutoRespawn;

		if (g_Cfg.fNoRespawnDelay > 0)
		{
			g_pNoRespawnTimer[iSlot] = g_pUtils->CreateTimer(g_Cfg.fNoRespawnDelay, [iSlot]() -> float {
				g_bRespawnReady[iSlot] = false;
				Notify(iSlot, "RespawnIsNoLongerAvailable");
				g_pNoRespawnTimer[iSlot] = nullptr;
				return -1.0f;
			});
		}

		if (g_Cfg.bAutoRespawn && g_Cfg.fNoAutoRespawnDelay > 0)
		{
			g_pNoAutoTimer[iSlot] = g_pUtils->CreateTimer(g_Cfg.fNoAutoRespawnDelay, [iSlot]() -> float {
				g_bAutoReady[iSlot] = false;
				Notify(iSlot, "AutoRespawnIsNoLongerAvailable");
				g_pNoAutoTimer[iSlot] = nullptr;
				return -1.0f;
			});
		}
	}
}

static void OnRoundEnd(const char*, IGameEvent*, bool)
{
	for (int i = 0; i < 64; ++i)
	{
		g_bRespawnReady[i] = false;
		g_bAutoReady[i]    = false;
	}
}

static void OnPlayerDeath(const char*, IGameEvent* pEvent, bool)
{
	int iSlot = pEvent->GetInt("userid");
	if (iSlot < 0 || iSlot >= 64) return;

	if (!g_pVIPCore->VIP_IsClientVIP(iSlot))                     return;
	if (!g_pVIPCore->VIP_GetClientFeatureBool(iSlot, "respawn")) return;
	if (g_Cfg.iMaxRespawns <= 0)                                 return;

	if (g_Cfg.bAutoRespawn && g_bAutoReady[iSlot]
	    && g_iRespawns[iSlot] < g_Cfg.iMaxRespawns)
	{
		if (CountOnlinePlayers() < g_Cfg.iAutoMinPlayers)
		{
			Notify(iSlot, "NotEnoughOnlinePlayersForAutoRespawn");
		}
		else if (!MinAlivePassed(iSlot))
		{
			Notify(iSlot, "RespawnBlockedMinAlive");
		}
		else
		{
			if (g_Cfg.fAutoRespawnDelay > 0)
			{
				g_pAutoDelayTimer[iSlot] = g_pUtils->CreateTimer(g_Cfg.fAutoRespawnDelay, [iSlot]() -> float {
					if (iSlot < 0 || iSlot >= 64) return -1.0f;
					if (!MinAlivePassed(iSlot))
					{
						Notify(iSlot, "RespawnBlockedMinAlive");
					}
					else
					{
						DoRespawn(iSlot, g_Cfg.iHPAfterAutoRespawn);
					}
					g_pAutoDelayTimer[iSlot] = nullptr;
					return -1.0f;
				});
			}
			else
			{
				DoRespawn(iSlot, g_Cfg.iHPAfterAutoRespawn);
			}
			return;
		}
	}

	if (g_iRespawns[iSlot] >= g_Cfg.iMaxRespawns) return;

	if (CountOnlinePlayers() < g_Cfg.iMinPlayers)
	{
		Notify(iSlot, "NotEnoughOnlinePlayersForRespawn");
		return;
	}

	if (g_Cfg.fRespawnDelay > 0)
	{
		g_pRespawnDelayTimer[iSlot] = g_pUtils->CreateTimer(g_Cfg.fRespawnDelay, [iSlot]() -> float {
			if (iSlot < 0 || iSlot >= 64) return -1.0f;
			g_bRespawnReady[iSlot] = true;
			NotifyCount(iSlot, "RespawnAvailable", g_Cfg.iMaxRespawns - g_iRespawns[iSlot]);
			g_pRespawnDelayTimer[iSlot] = nullptr;
			return -1.0f;
		});
	}
	else
	{
		g_bRespawnReady[iSlot] = true;
		NotifyCount(iSlot, "RespawnAvailable", g_Cfg.iMaxRespawns - g_iRespawns[iSlot]);
	}
}

bool vip_respawn::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY    (GetEngineFactory,     g_pSchemaSystem,    ISchemaSystem,    SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory,     engine,             IVEngineServer2,  SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetServerFactory,     g_pSource2Server,   ISource2Server,   SOURCE2SERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem,  IFileSystem,      FILESYSTEM_INTERFACE_VERSION);
	g_SMAPI->AddListener(this, this);
	return true;
}

bool vip_respawn::Unload(char*, size_t)
{
	if (g_pUtils)
		g_pUtils->ClearAllHooks(g_PLID);
	return true;
}

CGameEntitySystem* GameEntitySystem()
{
	return g_pVIPCore->VIP_GetEntitySystem();
}

static void OnStartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem     = g_pGameEntitySystem;
	LoadConfig();
}

static void OnVIPLoaded()
{
	g_pUtils->StartupServer(g_PLID, OnStartupServer);
	g_pUtils->HookEvent(g_PLID, "round_start",  OnRoundStart);
	g_pUtils->HookEvent(g_PLID, "round_end",    OnRoundEnd);
	g_pUtils->HookEvent(g_PLID, "player_death", OnPlayerDeath);
	g_pUtils->RegCommand(g_PLID,
		{ "mm_respawn", "sm_respawn", "respawn" },
		{ "!respawn", "respawn" },
		OnRespawnCommand);
}

static bool BindIface(void*& pTarget, const char* szIface, const char* szLabel)
{
	int ret;
	pTarget = g_SMAPI->MetaFactory(szIface, &ret, NULL);
	if (ret == META_IFACE_FAILED)
	{
		ConColorMsg(Color(255, 0, 0, 255), "[%s] %s lookup failed.\n",
			g_vip_respawn.GetLogTag(), szLabel);
		std::string sBuf = "meta unload " + std::to_string(g_PLID);
		engine->ServerCommand(sBuf.c_str());
		return false;
	}
	return true;
}

void vip_respawn::AllPluginsLoaded()
{
	if (!BindIface(*reinterpret_cast<void**>(&g_pVIPCore), VIP_INTERFACE,     "vip core"))   return;
	if (!BindIface(*reinterpret_cast<void**>(&g_pUtils),   Utils_INTERFACE,   "utils api"))  return;
	if (!BindIface(*reinterpret_cast<void**>(&g_pPlayers), PLAYERS_INTERFACE, "players api")) return;

	g_pVIPCore->VIP_OnVIPLoaded(OnVIPLoaded);
	g_pVIPCore->VIP_RegisterFeature("respawn", VIP_BOOL, SELECTABLE,
		OnMenuSelect, nullptr, OnMenuDisplay);
}

const char *vip_respawn::GetLicense()
{
	return "Public";
}

const char *vip_respawn::GetVersion()
{
	return "1.1";
}

const char *vip_respawn::GetDate()
{
	return __DATE__;
}

const char *vip_respawn::GetLogTag()
{
	return "[VIP-RESPAWN++]";
}

const char *vip_respawn::GetAuthor()
{
	return "_ded_cookies && E!N";
}

const char *vip_respawn::GetDescription()
{
	return "VIP Respawn++";
}

const char *vip_respawn::GetName()
{
	return "[VIP] Respawn++";
}

const char *vip_respawn::GetURL()
{
	return "https://api.onlypublic.net";
}
