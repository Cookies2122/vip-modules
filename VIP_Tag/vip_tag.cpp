#include <stdio.h>
#include <string.h>
#include <ctime>
#include "vip_tag.h"

VIPTag g_VIPTag;
IVIPApi*  g_pVIPCore = nullptr;
IUtilsApi* g_pUtils  = nullptr;
IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;
CGlobalVars* gpGlobals = nullptr;

#define VIP_TAG_COOKIE "vip_clantag_state"

PLUGIN_EXPOSE(VIPTag, g_VIPTag);

bool VIPTag::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	g_SMAPI->AddListener( this, this );
	return true;
}

static void OnStartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pGameEntitySystem;
	if (g_pUtils) gpGlobals = g_pUtils->GetCGlobalVars();
}

static inline float NowF() {
	return (float)std::time(nullptr);
}

static bool  g_NextlevelEventReady = false;
static float g_NextlevelEarliestAt = 0.0f;
static float g_NextlevelCooldown   = 5.0f;
static float g_NextlevelLastFire   = -9999.0f;
static char  g_LastNextlevel[64]   = "";
static char  g_LastSkirmish[64]    = "";

static void ArmNextlevelEventAfterWarmup(float delaySec = 10.0f) {
	g_NextlevelEventReady = true;
	g_NextlevelEarliestAt = NowF() + delaySec;
}

static void GetSafeNextlevelPayload(char (&outNext)[64], char (&outSkirmish)[64]) {
	outNext[0] = outSkirmish[0] = '\0';
	const char* cur = nullptr;
	if (gpGlobals) {
		const char* nm = gpGlobals->mapname.ToCStr();
		if (nm && *nm) cur = nm;
	}
	std::snprintf(outNext, sizeof(outNext), "%s", cur ? cur : "unknown");
	std::snprintf(outSkirmish, sizeof(outSkirmish), "%s", "default");
}

static void FireNextLevelChangedEvent_Safe(bool dontBroadcast = false, bool forceFire = false) {
	if (!g_pUtils) return;
	IGameEventManager2* em = g_pUtils->GetGameEventManager();
	if (!em) return;

	const float now = NowF();
	if (!g_NextlevelEventReady || now < g_NextlevelEarliestAt) {
		if (forceFire) {
			const float delay = (g_NextlevelEarliestAt > now) ? (g_NextlevelEarliestAt - now) : 0.1f;
			g_pUtils->CreateTimer(delay, [dontBroadcast]() -> float {
				FireNextLevelChangedEvent_Safe(dontBroadcast, false);
				return -1.0f;
			});
		}
		return;
	}

	if (!forceFire && (now - g_NextlevelLastFire < g_NextlevelCooldown)) {
		return;
	}

	char nextlvl[64], skirm[64];
	GetSafeNextlevelPayload(nextlvl, skirm);

	if (!forceFire) {
		if (std::strncmp(g_LastNextlevel, nextlvl, sizeof(nextlvl)) == 0 &&
		    std::strncmp(g_LastSkirmish,  skirm,  sizeof(skirm))    == 0) {
			return;
		}
	}

	IGameEvent* ev = em->CreateEvent("nextlevel_changed", false);
	if (!ev) return;

	ev->SetString("nextlevel",    nextlvl);
	ev->SetString("skirmishmode", skirm);

	em->FireEvent(ev, dontBroadcast);
	std::snprintf(g_LastNextlevel, sizeof(g_LastNextlevel), "%s", nextlvl);
	std::snprintf(g_LastSkirmish,  sizeof(g_LastSkirmish),  "%s", skirm);
	g_NextlevelLastFire = now;
}

static bool IsTagDisabledByCookie(int iSlot)
{
	if (!g_pVIPCore) return false;
	const char* c = g_pVIPCore->VIP_GetClientCookie(iSlot, VIP_TAG_COOKIE);
	return (c && !strcmp(c, "off"));
}

static bool VIP_TagToggleCallback(int iSlot, const char* szFeature, VIP_ToggleState eOld, VIP_ToggleState& eNew)
{
	CCSPlayerController* pc = CCSPlayerController::FromSlot(iSlot);
	if (eNew == DISABLED) {
		if (g_pVIPCore) g_pVIPCore->VIP_SetClientCookie(iSlot, VIP_TAG_COOKIE, "off");
		if (pc) pc->m_szClan() = CUtlSymbolLarge("\0");
	} else if (eNew == ENABLED) {
		if (g_pVIPCore) g_pVIPCore->VIP_SetClientCookie(iSlot, VIP_TAG_COOKIE, "on");
		if (pc) {
			const char* szClan = g_pVIPCore->VIP_GetClientFeatureString(iSlot, "clantag");
			if (szClan && strlen(szClan) > 0)
				pc->m_szClan() = CUtlSymbolLarge(szClan);
		}
	}
	if (pc && g_pUtils)
		g_pUtils->SetStateChanged(pc, "CCSPlayerController", "m_szClan");
	FireNextLevelChangedEvent_Safe(false, true);
	return false;
}

void VIP_OnPlayerSpawn(int iSlot, int iTeam, bool bIsVIP)
{
	if(!bIsVIP) return;

	CCSPlayerController* pPlayerController = CCSPlayerController::FromSlot(iSlot);
	if(!pPlayerController) return;

	if (IsTagDisabledByCookie(iSlot)) {
		pPlayerController->m_szClan() = CUtlSymbolLarge("\0");
		return;
	}

	const char* szClan = g_pVIPCore->VIP_GetClientFeatureString(iSlot, "clantag");
	if(szClan && strlen(szClan) > 0)
		pPlayerController->m_szClan() = CUtlSymbolLarge(szClan);
	else
		pPlayerController->m_szClan() = CUtlSymbolLarge("\0");
}

void VIP_OnVIPClientRemoved(int iSlot, int iReason)
{
	CCSPlayerController* pPlayerController = CCSPlayerController::FromSlot(iSlot);
	if(!pPlayerController) return;
	pPlayerController->m_szClan() = CUtlSymbolLarge("\0");
}

void VIP_OnVIPLoaded()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pGameEntitySystem;
	g_pVIPCore->VIP_OnPlayerSpawn(VIP_OnPlayerSpawn);
	g_pVIPCore->VIP_OnVIPClientRemoved(VIP_OnVIPClientRemoved);
}

void VIPTag::AllPluginsLoaded()
{
	int ret;
	g_pVIPCore = (IVIPApi*)g_SMAPI->MetaFactory(VIP_INTERFACE, &ret, NULL);

	if (ret == META_IFACE_FAILED)
	{
		char error[64];
		V_strncpy(error, "Failed to lookup vip core. Aborting", 64);
		ConColorMsg(Color(255, 0, 0, 255), "[%s] %s\n", GetLogTag(), error);
		std::string sBuffer = "meta unload "+std::to_string(g_PLID);
		engine->ServerCommand(sBuffer.c_str());
		return;
	}

	g_pUtils = (IUtilsApi*)g_SMAPI->MetaFactory(UTILS_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED) g_pUtils = nullptr;
	if (g_pUtils) {
		g_pUtils->StartupServer(g_PLID, OnStartupServer);
		gpGlobals = g_pUtils->GetCGlobalVars();
	}

	g_pVIPCore->VIP_OnVIPLoaded(VIP_OnVIPLoaded);
	g_pVIPCore->VIP_RegisterFeature("clantag", VIP_STRING, TOGGLABLE, nullptr, VIP_TagToggleCallback);

	ArmNextlevelEventAfterWarmup(10.0f);
}

bool VIPTag::Unload(char *error, size_t maxlen)
{
	return true;
}

const char *VIPTag::GetLicense()
{
	return "Public";
}

const char *VIPTag::GetVersion()
{
	return "1.2.1";
}

const char *VIPTag::GetDate()
{
	return __DATE__;
}

const char *VIPTag::GetLogTag()
{
	return "[VIP-TAG]";
}

const char *VIPTag::GetAuthor()
{
	return "Pisex";
}

const char *VIPTag::GetDescription()
{
	return "Puts a vip tag on the player";
}

const char *VIPTag::GetName()
{
	return "[VIP] Tag";
}

const char *VIPTag::GetURL()
{
	return "https://discord.com/invite/g798xERK5Y";
}
