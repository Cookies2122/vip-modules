#ifndef _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_
#define _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_

#include <ISmmPlugin.h>
#include <filesystem.h>
#include <igameevents.h>
#include "utlvector.h"
#include "ehandle.h"
#include <entity2/entitysystem.h>
#include "inetchannelinfo.h"
#include "CCSPlayerController.h"
#include "CGameRules.h"
#include "iserver.h"
#include "include/menus.h"
#include "include/utils.h"
#include "include/players.h"
#include "include/vip.h"
#include <ctime>

class vip_regen_armor : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	void AllPluginsLoaded();
public:
	const char *GetAuthor();
	const char *GetName();
	const char *GetDescription();
	const char *GetURL();
	const char *GetLicense();
	const char *GetVersion();
	const char *GetDate();
	const char *GetLogTag();
};

extern vip_regen_armor g_vip_regen_armor;

PLUGIN_GLOBALVARS();

#endif
