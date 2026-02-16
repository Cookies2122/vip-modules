#include <stdio.h>
#include "vip_weaponkit.h"
#include "schemasystem/schemasystem.h"
#include <sstream>

vip_weaponkit g_vip_weaponkit;

IVIPApi* g_pVIPCore;
IUtilsApi* g_pUtils;
IMenusApi* g_pMenus;

CCSGameRules* g_pGameRules = nullptr;
IVEngineServer2* engine = nullptr;
CGameEntitySystem* g_pGameEntitySystem = nullptr;
CEntitySystem* g_pEntitySystem = nullptr;

PLUGIN_EXPOSE(vip_weaponkit, g_vip_weaponkit);

int g_iRoundMin = 0;
int g_iRoundLimit = 0;
bool g_bAutoOpenMenu = true;

struct WeaponKit {
    std::string id;
    std::string name;
    int team;
    std::vector<std::string> weapons;
};

std::map<std::string, WeaponKit> g_Kits;
std::map<int, std::string> g_SavedKit;
std::map<int, int> g_NextAvailableRound;
std::map<int, int> g_LastNotifyRound;

const char* GetTranslation(const char* key) {
    if (!g_pVIPCore) {
        if (!strcmp(key, "Weaponkit")) return "Комплект оружий";
        if (!strcmp(key, "KitReceived")) return "Вы получили комплект!";
        if (!strcmp(key, "SelectionSaved")) return "Выбор сохранён!";
        return key;
    }
    
    const char* translation = g_pVIPCore->VIP_GetTranslate(key);

    if (translation && translation[0]) {
        return translation;
    }

    if (!strcmp(key, "Prefix")) return " {GREEN}[VIP]{DEFAULT}";
    if (!strcmp(key, "NotAccess")) return "У вас нету доступа к этой команде";
    if (!strcmp(key, "Weaponkit")) return "Комплект оружий";
    if (!strcmp(key, "KitReceived")) return "Вы получили комплект!";
    if (!strcmp(key, "KitAvailable")) return "Комплекты оружия доступны! Напишите {GREEN}!wkit{DEFAULT} для выбора";
    if (!strcmp(key, "KitFromRound")) return "Комплекты доступны с {GREEN}%d{DEFAULT} раунда!";
    if (!strcmp(key, "KitNextRound")) return "Следующий комплект можно взять через {GREEN}%d{DEFAULT} раунд(а)!";
    if (!strcmp(key, "NoKitsAvailable")) return "Нет доступных комплектов для вашей команды!";
    if (!strcmp(key, "SelectionSaved")) return "Выбор сохранён! Получите при спавне";
    if (!strcmp(key, "SelectionRemoved")) return "Выбор снят! При спавне откроется меню";
    
    return key;
}

void LoadConfig() {
    g_Kits.clear();
    
    KeyValues* kv = new KeyValues("WeaponKit");
    const char* path = "addons/configs/vip/vip_weaponkit.ini";
    
    if (!kv->LoadFromFile(g_pFullFileSystem, path)) {
        g_pUtils->ErrorLog("[%s] Failed to load %s", g_PLAPI->GetLogTag(), path);
        delete kv;
        return;
    }
    
    g_iRoundMin = kv->GetInt("round_min", 0);
    g_iRoundLimit = kv->GetInt("roundlimit", 0);
    g_bAutoOpenMenu = kv->GetInt("autoopenmenu", 1) != 0;
    
    FOR_EACH_SUBKEY(kv, pSubKey) {
        const char* keyName = pSubKey->GetName();
        
        if (!strcmp(keyName, "round_min") || 
            !strcmp(keyName, "roundlimit") || 
            !strcmp(keyName, "autoopenmenu")) {
            continue;
        }
        
        WeaponKit kit;
        kit.id = keyName;
        kit.name = pSubKey->GetString("name", keyName);
        kit.team = pSubKey->GetInt("team", 0);
        
        FOR_EACH_VALUE(pSubKey, pValue) {
            const char* valueName = pValue->GetName();
            if (!strcmp(valueName, "weapon")) {
                const char* weapon = pValue->GetString(nullptr, "");
                if (weapon && weapon[0]) {
                    kit.weapons.push_back(weapon);
                }
            }
        }
        
        if (!kit.weapons.empty()) {
            g_Kits[kit.id] = kit;
        }
    }
    
    delete kv;
}

std::string LoadPlayerData(int iSlot) {
    if (!g_pVIPCore) return "";
    
    const char* saved = g_pVIPCore->VIP_GetClientCookie(iSlot, "weaponkit");
    if (saved && saved[0]) {
        return std::string(saved);
    }
    
    return "";
}

void SavePlayerData(int iSlot, const std::string& kitId) {
    if (!g_pVIPCore) return;
    
    g_pVIPCore->VIP_SetClientCookie(iSlot, "weaponkit", kitId.c_str());
}

std::vector<std::string> GetPlayerKits(int iSlot) {
    std::vector<std::string> kits;
    
    CCSPlayerController* pController = CCSPlayerController::FromSlot(iSlot);
    if (!pController) return kits;
    
    const char* feature = g_pVIPCore->VIP_GetClientFeatureString(iSlot, "WeaponKit");
    if (!feature || !feature[0] || !strcmp(feature, "none")) return kits;
    
    std::string strFeature = feature;
    if (strFeature == "all") {
        for (const auto& [id, kit] : g_Kits) {
            kits.push_back(id);
        }
        return kits;
    }
    
    std::istringstream iss(strFeature);
    std::string kitId;
    while (std::getline(iss, kitId, ';')) {
        if (!kitId.empty() && g_Kits.find(kitId) != g_Kits.end()) {
            kits.push_back(kitId);
        }
    }
    
    return kits;
}

bool GiveKit(int iSlot, const std::string& kitId) {
    auto it = g_Kits.find(kitId);
    if (it == g_Kits.end()) return false;
    
    CCSPlayerController* pController = CCSPlayerController::FromSlot(iSlot);
    if (!pController) return false;
    
    CCSPlayerPawnBase* pPawn = pController->m_hPlayerPawn();
    if (!pPawn || pPawn->m_lifeState() != LIFE_ALIVE) return false;
    
    int playerTeam = pController->m_iTeamNum();
    if (it->second.team != 0 && it->second.team != playerTeam) return false;
    
    CCSPlayer_ItemServices* pItemServices = static_cast<CCSPlayer_ItemServices*>(pPawn->m_pItemServices());
    if (!pItemServices) return false;
    
    for (const auto& weapon : it->second.weapons) {
        if (!weapon.empty()) {
            pItemServices->GiveNamedItem(weapon.c_str());
        }
    }
    
    if (g_pUtils) {
        g_pUtils->PrintToChat(iSlot, "%s %s",
            GetTranslation("Prefix"), 
            GetTranslation("KitReceived"));
    }
    
    return true;
}

bool CanGive(int iSlot, bool showMessage = true) {
    if (!g_pVIPCore) return false;
    
    int currentRound = g_pVIPCore->VIP_GetTotalRounds();
    
    if (currentRound < g_iRoundMin) {
        if (showMessage) {
            g_pUtils->PrintToChat(iSlot, "%s %s",
                GetTranslation("Prefix"), 
                GetTranslation("KitFromRound"));
        }
        return false;
    }
    
    if (g_iRoundLimit > 0) {
        int nextRound = g_NextAvailableRound[iSlot];
        if (nextRound > currentRound) {
            if (showMessage) {
                g_pUtils->PrintToChat(iSlot, "%s %s",
                    GetTranslation("Prefix"), 
                    GetTranslation("KitNextRound"));
            }
            return false;
        }
    }
    
    return true;
}

bool ShowMenu(int iSlot);

void MenuCallback(const char* szBack, const char* szFront, int iItem, int iSlot) {
    if (!g_pVIPCore || !g_pVIPCore->VIP_IsClientVIP(iSlot)) return;
    
    // Если пустой - возврат в VIP меню
    if (!szBack || szBack[0] == '\0') {
        g_pVIPCore->VIP_OpenMenu(iSlot);
        return;
    }

    if (!strcmp(szBack, "exit")) {
        return;
    }
    
    std::string kitId = szBack;

    if (g_Kits.find(kitId) == g_Kits.end()) {
        return;
    }
    
    if (g_SavedKit[iSlot] == kitId) {
        g_SavedKit[iSlot] = "";
        SavePlayerData(iSlot, "");
        
        if (g_pUtils) {
            g_pUtils->PrintToChat(iSlot, "%s %s",
                GetTranslation("Prefix"), 
                GetTranslation("SelectionRemoved"));
        }
        
        ShowMenu(iSlot);
        return;
    }

    g_SavedKit[iSlot] = kitId;
    SavePlayerData(iSlot, kitId);
    
    if (CanGive(iSlot, false)) {
        if (GiveKit(iSlot, kitId)) {
            if (g_iRoundLimit > 0) {
                int currentRound = g_pVIPCore->VIP_GetTotalRounds();
                g_NextAvailableRound[iSlot] = currentRound + g_iRoundLimit;
            }
        } else {
            if (g_pUtils) {
                g_pUtils->PrintToChat(iSlot, "%s %s",
                    GetTranslation("Prefix"), 
                    GetTranslation("SelectionSaved"));
            }
        }
    } else {
        if (g_pUtils) {
            g_pUtils->PrintToChat(iSlot, "%s %s",
                GetTranslation("Prefix"), 
                GetTranslation("SelectionSaved"));
        }
    }
    
    ShowMenu(iSlot);
}

bool ShowMenu(int iSlot) {
    if (!g_pVIPCore || !g_pVIPCore->VIP_IsClientVIP(iSlot)) return false;
    if (!g_pMenus) return false;
    
    CCSPlayerController* pController = CCSPlayerController::FromSlot(iSlot);
    if (!pController) return false;
    
    std::vector<std::string> kits = GetPlayerKits(iSlot);
    if (kits.empty()) {
        g_pUtils->PrintToChat(iSlot, "%s %s", 
            GetTranslation("Prefix"), 
            GetTranslation("NoKitsAvailable"));
        return false;
    }
    
    int playerTeam = pController->m_iTeamNum();
    
    Menu menu;
    g_pMenus->SetTitleMenu(menu, GetTranslation("Weaponkit"));
    g_pMenus->SetExitMenu(menu, true);
    g_pMenus->SetCallback(menu, MenuCallback);
    
    std::string currentKit = g_SavedKit[iSlot];
    
    for (const auto& kitId : kits) {
        auto it = g_Kits.find(kitId);
        if (it == g_Kits.end()) continue;
        
        if (it->second.team != 0 && it->second.team != playerTeam) continue;
        
        std::string display = it->second.name;
        if (kitId == currentKit) {
            display = "[✓] " + display;
        }
        
        g_pMenus->AddItemMenu(menu, kitId.c_str(), display.c_str());
    }
    
    g_pMenus->DisplayPlayerMenu(menu, iSlot, true, true);
    return true;
}

bool CMD_WeaponKit(int iSlot, const char* szContent) {
    if (!g_pVIPCore || !g_pVIPCore->VIP_IsClientVIP(iSlot)) {
        g_pUtils->PrintToChat(iSlot, "%s %s",
            GetTranslation("Prefix"), 
            GetTranslation("NotAccess"));
        return true;
    }
    
    ShowMenu(iSlot);
    return true;
}

void VIP_OnPlayerSpawn(int iSlot, int iTeam, bool bIsVIP) {
    if (!bIsVIP || !g_pVIPCore) return;
    
    int currentRound = g_pVIPCore->VIP_GetTotalRounds();
    
    static std::map<int, int> lastSpawnRound;
    if (lastSpawnRound[iSlot] == currentRound) return;
    lastSpawnRound[iSlot] = currentRound;
    
    std::string savedKit = g_SavedKit[iSlot];
    
    std::vector<std::string> kits = GetPlayerKits(iSlot);
    bool hasKits = !kits.empty();
    
    if (!hasKits) return;
    
    if (currentRound < g_iRoundMin) {
        if (savedKit.empty() && g_bAutoOpenMenu && g_LastNotifyRound[iSlot] != currentRound) {
            char msg[256];
            snprintf(msg, sizeof(msg), GetTranslation("KitFromRound"), g_iRoundMin);
            g_pUtils->PrintToChat(iSlot, "%s %s", GetTranslation("Prefix"), msg);
            g_LastNotifyRound[iSlot] = currentRound;
        }
        return;
    }
    
    if (g_iRoundLimit > 0 && g_NextAvailableRound[iSlot] > currentRound) {
        if (savedKit.empty() && g_bAutoOpenMenu && g_LastNotifyRound[iSlot] != currentRound) {
            int roundsLeft = g_NextAvailableRound[iSlot] - currentRound;
            char msg[256];
            snprintf(msg, sizeof(msg), GetTranslation("KitNextRound"), roundsLeft);
            g_pUtils->PrintToChat(iSlot, "%s %s", GetTranslation("Prefix"), msg);
            g_LastNotifyRound[iSlot] = currentRound;
        }
        return;
    }
    
    if (savedKit.empty() && g_bAutoOpenMenu) {
        if (g_LastNotifyRound[iSlot] != currentRound) {
            ShowMenu(iSlot);
            g_LastNotifyRound[iSlot] = currentRound;
        }
        return;
    }
    
    if (!savedKit.empty()) {
        if (!CanGive(iSlot, false)) return;
        
        bool hasAccess = std::find(kits.begin(), kits.end(), savedKit) != kits.end();
        if (!hasAccess) return;
        
        if (GiveKit(iSlot, savedKit)) {
            if (g_iRoundLimit > 0) {
                g_NextAvailableRound[iSlot] = currentRound + g_iRoundLimit;
            }
        }
    }
}

void VIP_OnClientLoaded(int iSlot, bool bIsVIP) {
    g_SavedKit[iSlot] = "";
    g_NextAvailableRound[iSlot] = 0;
    g_LastNotifyRound[iSlot] = 0;
    
    if (bIsVIP) {
        std::string kitId = LoadPlayerData(iSlot);
        if (!kitId.empty()) {
            g_SavedKit[iSlot] = kitId;
        }
    }
}

bool VIP_WeaponkitMenu(int iSlot, const char* szValue) {
    ShowMenu(iSlot);
    return false;
}

CGameEntitySystem* GameEntitySystem() {
    return g_pUtils->GetCGameEntitySystem();
}

void OnStartupServer() {
    g_pGameEntitySystem = GameEntitySystem();
    g_pEntitySystem = g_pGameEntitySystem;
    LoadConfig();
}

void GetGameRules() {
    g_pGameRules = g_pUtils->GetCCSGameRules();
}

bool vip_weaponkit::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late) {
    PLUGIN_SAVEVARS();
    GET_V_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
    g_SMAPI->AddListener(this, this);
    return true;
}

void vip_weaponkit::AllPluginsLoaded() {
    int ret;
    
    g_pUtils = (IUtilsApi*)g_SMAPI->MetaFactory(Utils_INTERFACE, &ret, NULL);
    if (ret == META_IFACE_FAILED) {
        char error[64];
        V_strncpy(error, "Failed to lookup utils api. Aborting", 64);
        ConColorMsg(Color(255, 0, 0, 255), "[%s] %s\n", GetLogTag(), error);
        std::string sBuffer = "meta unload "+std::to_string(g_PLID);
        engine->ServerCommand(sBuffer.c_str());
        return;
    }
    
    g_pMenus = (IMenusApi*)g_SMAPI->MetaFactory(Menus_INTERFACE, &ret, NULL);
    if (ret == META_IFACE_FAILED) {
        g_pUtils->ErrorLog("[%s] Failed to lookup menus api. Aborting", GetLogTag());
        std::string sBuffer = "meta unload "+std::to_string(g_PLID);
        engine->ServerCommand(sBuffer.c_str());
        return;
    }
    
    g_pVIPCore = (IVIPApi*)g_SMAPI->MetaFactory(VIP_INTERFACE, &ret, NULL);
    if (ret == META_IFACE_FAILED) {
        g_pUtils->ErrorLog("[%s] Failed to lookup vip core. Aborting", GetLogTag());
        std::string sBuffer = "meta unload "+std::to_string(g_PLID);
        engine->ServerCommand(sBuffer.c_str());
        return;
    }
    
    g_pUtils->StartupServer(g_PLID, OnStartupServer);
    g_pUtils->OnGetGameRules(g_PLID, GetGameRules);
    g_pVIPCore->VIP_OnPlayerSpawn(VIP_OnPlayerSpawn);
    g_pVIPCore->VIP_OnClientLoaded(VIP_OnClientLoaded);
    
    g_pUtils->RegCommand(g_PLID, {}, {"!wkit", "!weaponkit"}, CMD_WeaponKit);
    
    g_pVIPCore->VIP_RegisterFeature("WeaponKit", VIP_STRING, HIDE);
    g_pVIPCore->VIP_RegisterFeature("WeaponkitMenu", VIP_BOOL, SELECTABLE, VIP_WeaponkitMenu);
}

bool vip_weaponkit::Unload(char* error, size_t maxlen) {
    return true;
}

const char *vip_weaponkit::GetLicense()
{
    return "Public";
}

const char *vip_weaponkit::GetVersion()
{
    return "1.1";
}

const char *vip_weaponkit::GetDate()
{
    return __DATE__;
}

const char *vip_weaponkit::GetLogTag()
{
    return "[VIP-WEAPONKIT]";
}

const char *vip_weaponkit::GetAuthor()
{
    return "_ded_cookies";
}

const char *vip_weaponkit::GetDescription()
{
    return "VIP Weapon Kit System";
}

const char *vip_weaponkit::GetName()
{
    return "VIP Weapon Kit";
}

const char *vip_weaponkit::GetURL()
{
    return "https://api.onlypublic.net/";
}