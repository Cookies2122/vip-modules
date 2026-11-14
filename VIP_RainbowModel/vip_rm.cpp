#include <stdio.h>
#include "vip_rm.h"
#include "schemasystem/schemasystem.h"
#include <khook.hpp>

vip_rm g_vip_rm;

IVIPApi* g_pVIPCore;
IUtilsApi* g_pUtils;

IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;

int iCountTick = 0;
int g_iGradient[3], gI_GradientDirection = -1;

enum
{
	RED = 0,
	GREEN,
	BLUE
};

PLUGIN_EXPOSE(vip_rm, g_vip_rm);

KHook::Return<void> Hook_GameFrame(IServerGameDLL* pServer, bool simulating, bool bFirstTick, bool bLastTick)
{
	g_vip_rm.GameFrame(simulating, bFirstTick, bLastTick);
	return { KHook::Action::Ignore };
}

KHook::Virtual<IServerGameDLL, void, bool, bool, bool> g_hkGameFrame(&IServerGameDLL::GameFrame, nullptr, &Hook_GameFrame);
bool vip_rm::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();
	GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetServerFactory, g_pSource2Server, ISource2Server, SOURCE2SERVER_INTERFACE_VERSION);
	g_SMAPI->AddListener( this, this );
	g_hkGameFrame.Add(g_pSource2Server);
	return true;
}

void GetRainbow()
{
	switch(gI_GradientDirection)
	{
		case 0:
		{
			g_iGradient[BLUE] += 15;

			if(g_iGradient[BLUE] >= 255)
			{
				g_iGradient[BLUE] = 255;
				gI_GradientDirection = 1;
			}
			break;
		}

		case 1:
		{
			g_iGradient[RED] -= 15;

			if(g_iGradient[RED] <= 180)
			{
				g_iGradient[RED] = 180;
				gI_GradientDirection = 2;
			}
			break;
		}

		case 2:
		{
			g_iGradient[GREEN] += 15;

			if(g_iGradient[GREEN] >= 255)
			{
				g_iGradient[GREEN] = 255;
				gI_GradientDirection = 3;
			}
			break;
		}

		case 3:
		{
			g_iGradient[BLUE] -= 15;

			if(g_iGradient[BLUE] <= 0)
			{
				g_iGradient[BLUE] = 0;
				gI_GradientDirection = 4;
			}
			break;
		}

		case 4:
		{
			g_iGradient[RED] += 15;

			if(g_iGradient[RED] >= 255)
			{
				g_iGradient[RED] = 255;
				gI_GradientDirection = 5;
			}
			break;
		}

		case 5:
		{
			g_iGradient[GREEN] -= 15;

			if(g_iGradient[GREEN] <= 125)
			{
				g_iGradient[GREEN] = 125;
				gI_GradientDirection = 0;
			}
			break;
		}

		default:
		{
			g_iGradient[RED] = 255;
			gI_GradientDirection = 0;
			break;
		}
	}
}

void vip_rm::GameFrame(bool simulating, bool bFirstTick, bool bLastTick)
{
	if((iCountTick % 5) == 0)
	{
		GetRainbow();
		if(g_pVIPCore->VIP_IsVIPLoaded())
		{
			for (int i = 0; i < 64; i++)
			{
				CCSPlayerController* pPlayerController =  CCSPlayerController::FromSlot(i);
				if(!pPlayerController) continue;
				CCSPlayerPawnBase* pPlayerPawn = pPlayerController->m_hPlayerPawn();
				if (!pPlayerPawn || !pPlayerPawn->IsAlive()) continue;
				if(!g_pVIPCore->VIP_GetClientFeatureBool(i, "rainbow_model")) continue;
				pPlayerPawn->m_clrRender().SetColor(g_iGradient[RED], g_iGradient[GREEN], g_iGradient[BLUE], 255);
        		g_pUtils->SetStateChanged(pPlayerPawn, "CBaseModelEntity", "m_clrRender");
			}
		}
	}
	iCountTick++;
}

bool vip_rm::Unload(char *error, size_t maxlen)
{
	g_hkGameFrame.Remove(g_pSource2Server);
	return true;
}

void OnStartupServer()
{
	g_pGameEntitySystem = GameEntitySystem();
	g_pEntitySystem = g_pGameEntitySystem;
}

void vip_rm::AllPluginsLoaded()
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
	g_pVIPCore->VIP_RegisterFeature("rainbow_model", VIP_BOOL, TOGGLABLE);
}

const char *vip_rm::GetLicense()
{
	return "Public";
}

const char *vip_rm::GetVersion()
{
	return "1.0";
}

const char *vip_rm::GetDate()
{
	return __DATE__;
}

const char *vip_rm::GetLogTag()
{
	return "[VIP-RM]";
}

const char *vip_rm::GetAuthor()
{
	return "Pisex";
}

const char *vip_rm::GetDescription()
{
	return "";
}

const char *vip_rm::GetName()
{
	return "[VIP] Raibow Model";
}

const char *vip_rm::GetURL()
{
	return "https://discord.com/invite/g798xERK5Y";
}
