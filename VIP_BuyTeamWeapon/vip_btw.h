#ifndef _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_
#define _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_

#include <ISmmPlugin.h>
#include <filesystem.h>
#include <igameevents.h>
#include "utlvector.h"
#include "ehandle.h"
#include <entity2/entitysystem.h>
#include "CCSPlayerController.h"
#include "iserver.h"
#include "include/vip.h"
#include "include/menus.h"
#include "include/utils.h"
#include "include/players.h"
#include <ctime>

class vip_btw : public ISmmPlugin, public IMetamodListener
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

extern vip_btw g_vip_btw;

PLUGIN_GLOBALVARS();

#endif
