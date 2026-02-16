#ifndef _INCLUDE_METAMOD_SOURCE_VIP_WEAPONKIT_H_
#define _INCLUDE_METAMOD_SOURCE_VIP_WEAPONKIT_H_

#include <ISmmPlugin.h>
#include <igameevents.h>
#include <iplayerinfo.h>
#include "utlvector.h"
#include "ehandle.h"
#include <sh_vector.h>
#include <entity2/entitysystem.h>
#include "CCSPlayerController.h"
#include "iserver.h"
#include "include/vip.h"
#include "include/menus.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class vip_weaponkit final : public ISmmPlugin, public IMetamodListener
{
public:
    bool Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late);
    bool Unload(char* error, size_t maxlen);
    void AllPluginsLoaded();

public:
    const char* GetAuthor();
    const char* GetName();
    const char* GetDescription();
    const char* GetURL();
    const char* GetLicense();
    const char* GetVersion();
    const char* GetDate();
    const char* GetLogTag();
};

extern vip_weaponkit g_vip_weaponkit;

PLUGIN_GLOBALVARS();

#endif 
