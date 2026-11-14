#include <stdio.h>
#include "vip_duckspeed.h"
#include "metamod_oslink.h"
#include "schemasystem/schemasystem.h"

vip_duckspeed g_vip_duckspeed;
PLUGIN_EXPOSE(vip_duckspeed, g_vip_duckspeed);
IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;
CGlobalVars *gpGlobals = nullptr;

IUtilsApi* g_pUtils;
IVIPApi* g_pVIPCore;

float g_flDuckSpeed[64] = {0.0f};
int g_iDuckSpeedCount = 0;

void StartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pUtils->GetCEntitySystem();
	gpGlobals = g_pUtils->GetCGlobalVars();
	for (int i = 0; i < 64; i++) g_flDuckSpeed[i] = 0.0f;
	g_iDuckSpeedCount = 0;
}

void VIP_OnPlayerSpawn(int iSlot, int iTeam, bool bIsVIP)
{
	if (g_flDuckSpeed[iSlot] > 0.0f) g_iDuckSpeedCount--;

	if (bIsVIP)
	{
		float fDuckSpeed = g_pVIPCore->VIP_GetClientFeatureFloat(iSlot, "duckspeed");
		if (fDuckSpeed > 0.0f)
		{
			g_flDuckSpeed[iSlot] = fDuckSpeed;
			g_iDuckSpeedCount++;
		}
		else
		{
			g_flDuckSpeed[iSlot] = 0.0f;
		}
	}
	else
	{
		g_flDuckSpeed[iSlot] = 0.0f;
	}
}

float DuckSpeedTimer()
{
	if (!g_pGameEntitySystem || g_iDuckSpeedCount <= 0) return 0.0f;

	for (int i = 0; i < 64; i++)
	{
		if (g_flDuckSpeed[i] <= 0.0f) continue;

		CCSPlayerController* pPlayerController = CCSPlayerController::FromSlot(i);
		if (!pPlayerController) continue;

		CCSPlayerPawn* pPlayerPawn = pPlayerController->m_hPlayerPawn();
		if (!pPlayerPawn || !pPlayerPawn->IsAlive()) continue;

		CCSPlayer_MovementServices* pMovementServices = pPlayerPawn->m_pMovementServices();
		if (pMovementServices)
		{
			uint64* pButtons = pMovementServices->m_nButtons().m_pButtonStates();
			if (pButtons && (pButtons[0] & IN_DUCK))
			{
				pMovementServices->m_flDuckSpeed() = g_flDuckSpeed[i];
			}
		}
	}
	return 0.0f;
}

bool vip_duckspeed::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);

	g_SMAPI->AddListener( this, this );

	return true;
}

bool vip_duckspeed::Unload(char *error, size_t maxlen)
{
	ConVar_Unregister();
	return true;
}

void vip_duckspeed::AllPluginsLoaded()
{
	char error[64];
	int ret;
	g_pUtils = (IUtilsApi *)g_SMAPI->MetaFactory(UTILS_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED)
	{
		g_SMAPI->Format(error, sizeof(error), "Missing Utils system plugin");
		ConColorMsg(Color(255, 0, 0, 255), "[%s] %s\n", GetLogTag(), error);
		std::string sBuffer = "meta unload "+std::to_string(g_PLID);
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

	g_pUtils->StartupServer(g_PLID, StartupServer);
	g_pUtils->CreateTimer(0.0f, DuckSpeedTimer);
	g_pVIPCore->VIP_OnPlayerSpawn(VIP_OnPlayerSpawn);
	g_pVIPCore->VIP_RegisterFeature("duckspeed", VIP_FLOAT, HIDE);
}

const char* vip_duckspeed::GetLicense()
{
	return "Public";
}

const char* vip_duckspeed::GetVersion()
{
	return "1.0.0";
}

const char* vip_duckspeed::GetDate()
{
	return __DATE__;
}

const char *vip_duckspeed::GetLogTag()
{
	return "[VIP-DuckSpeed]";
}

const char* vip_duckspeed::GetAuthor()
{
	return "ABKAM";
}

const char* vip_duckspeed::GetDescription()
{
	return "[VIP] DuckSpeed";
}

const char* vip_duckspeed::GetName()
{
	return "[VIP] DuckSpeed";
}

const char* vip_duckspeed::GetURL()
{
	return "https://discord.gg/ChYfTtrtmS";
}
