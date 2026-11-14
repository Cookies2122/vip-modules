#include <stdio.h>
#include "vip_endurance.h"
#include "schemasystem/schemasystem.h"
#include <khook.hpp>

VIPEndurance g_VIPEndurance;

IVIPApi* g_pVIPCore;
IUtilsApi* g_pUtils;

IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;

bool g_bEndurance[64];
PLUGIN_EXPOSE(VIPEndurance, g_VIPEndurance);

KHook::Return<void> Hook_GameFrame(IServerGameDLL* pServer, bool simulating, bool bFirstTick, bool bLastTick)
{
	g_VIPEndurance.GameFrame(simulating, bFirstTick, bLastTick);
	return { KHook::Action::Ignore };
}

KHook::Virtual<IServerGameDLL, void, bool, bool, bool> g_hkGameFrame(&IServerGameDLL::GameFrame, nullptr, &Hook_GameFrame);

bool VIPEndurance::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetServerFactory, g_pSource2Server, ISource2Server, SOURCE2SERVER_INTERFACE_VERSION);
	g_hkGameFrame.Add(g_pSource2Server);
	g_SMAPI->AddListener( this, this );
	return true;
}

bool VIPEndurance::Unload(char *error, size_t maxlen)
{
	g_hkGameFrame.Remove(g_pSource2Server);
	return true;
}

void VIPEndurance::GameFrame(bool simulating, bool bFirstTick, bool bLastTick)
{
	if(g_pVIPCore->VIP_IsVIPLoaded())
	{
		for (int i = 0; i < 64; i++)
		{
			CCSPlayerController* pPlayerController = CCSPlayerController::FromSlot(i);
			if(!pPlayerController) continue;
			CCSPlayerPawn* pPlayerPawn = pPlayerController->m_hPlayerPawn();
			if (!pPlayerPawn || !pPlayerPawn->IsAlive())
				continue;
			if(g_bEndurance[i] && pPlayerPawn->m_flVelocityModifier() < 1.0)
			{
				pPlayerPawn->m_flVelocityModifier() = 1.0;
			}
		}
	}
}

void OnClientLoaded(int iSlot, bool bIsVIP)
{
	if(bIsVIP)
		g_bEndurance[iSlot] = g_pVIPCore->VIP_GetClientFeatureBool(iSlot, "Endurance");
	else
		g_bEndurance[iSlot] = false;
}

void OnClientDisconnect(int iSlot, bool bIsVIP)
{
	g_bEndurance[iSlot] = false;
}

bool OnTogglable(int iSlot, const char* szFeature, VIP_ToggleState eOldStatus, VIP_ToggleState& eNewStatus)
{
	g_bEndurance[iSlot] = (eNewStatus == ENABLED);
	return false;
}

void OnStartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pGameEntitySystem;
}

void VIPEndurance::AllPluginsLoaded()
{
	int ret;
	g_pUtils = (IUtilsApi*)g_SMAPI->MetaFactory(UTILS_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED)
	{
		char error[64];
		V_strncpy(error, "Failed to lookup utils api. Aborting", 64);
		ConColorMsg(Color(255, 0, 0, 255), "[%s] %s\n", GetLogTag(), error);
		std::string sBuffer = "meta unload "+std::to_string(g_PLID);
		engine->ServerCommand(sBuffer.c_str());
		return;
	}
	g_pVIPCore = (IVIPApi*)g_SMAPI->MetaFactory(VIP_INTERFACE, &ret, NULL);
	if (ret == META_IFACE_FAILED)
	{
		g_pUtils->ErrorLog("[%s] Failed to lookup vip core. Aborting", GetLogTag());
		std::string sBuffer = "meta unload "+std::to_string(g_PLID);
		engine->ServerCommand(sBuffer.c_str());
		return;
	}

	g_pUtils->StartupServer(g_PLID, OnStartupServer);
	g_pVIPCore->VIP_OnClientLoaded(OnClientLoaded);
	g_pVIPCore->VIP_OnClientDisconnect(OnClientDisconnect);
	g_pVIPCore->VIP_RegisterFeature("Endurance", VIP_BOOL, TOGGLABLE, nullptr, OnTogglable);
}

const char *VIPEndurance::GetLicense()
{
	return "Public";
}

const char *VIPEndurance::GetVersion()
{
	return "1.0";
}

const char *VIPEndurance::GetDate()
{
	return __DATE__;
}

const char *VIPEndurance::GetLogTag()
{
	return "[VIP-Endurance]";
}

const char *VIPEndurance::GetAuthor()
{
	return "Pisex";
}

const char *VIPEndurance::GetDescription()
{
	return "";
}

const char *VIPEndurance::GetName()
{
	return "[VIP] Endurance";
}

const char *VIPEndurance::GetURL()
{
	return "https://discord.com/invite/g798xERK5Y";
}
