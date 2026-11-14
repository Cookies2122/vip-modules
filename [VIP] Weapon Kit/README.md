# [VIP] Weapon Kit

VIP игрок выбирает себе набор оружия (кит) в меню, и в начале раунда получает его.

Автор: [\_ded\_cookies](https://github.com/Cookies2122).

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"WeaponKit"      "all"
"WeaponkitMenu"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `WeaponKit` | `all` все киты, или id китов через запятую, например `ak_t,awp_all` |
| `WeaponkitMenu` | пункт в меню VIP для выбора кита |

## Команды

| Команда | Что делает |
| --- | --- |
| `!wkit` | открыть выбор кита |
| `!weaponkit` | то же самое |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"WeaponkitMenu"
{
	"en"		"Weapon kit"
	"ru"		"Набор оружия"
}
```

Фразы `Prefix`, `NotAccess` уже есть в vip.phrases.txt ядра.

Остальные фразы можно не добавлять: если их нет, модуль пишет встроенные русские тексты. Чтобы поменять текст или добавить английский, допишите:

<details>
<summary>Необязательные фразы (8)</summary>

```
"Weaponkit"
{
	"en"		"Weapon kit"
	"ru"		"Комплект оружий"
}
"KitReceived"
{
	"en"		"You received a weapon kit!"
	"ru"		"Вы получили комплект!"
}
"KitAvailable"
{
	"en"		"Weapon kits are available! Type {GREEN}!wkit{DEFAULT} to choose"
	"ru"		"Комплекты оружия доступны! Напишите {GREEN}!wkit{DEFAULT} для выбора"
}
"KitFromRound"
{
	"en"		"Weapon kits are available from round {GREEN}%d{DEFAULT}!"
	"ru"		"Комплекты доступны с {GREEN}%d{DEFAULT} раунда!"
}
"KitNextRound"
{
	"en"		"Next kit is available in {GREEN}%d{DEFAULT} round(s)!"
	"ru"		"Следующий комплект можно взять через {GREEN}%d{DEFAULT} раунд(а)!"
}
"NoKitsAvailable"
{
	"en"		"No kits available for your team!"
	"ru"		"Нет доступных комплектов для вашей команды!"
}
"SelectionSaved"
{
	"en"		"Selection saved! You will get it on spawn"
	"ru"		"Выбор сохранён! Получите при спавне"
}
"SelectionRemoved"
{
	"en"		"Selection removed! The menu will open on spawn"
	"ru"		"Выбор снят! При спавне откроется меню"
}
```

</details>

## Конфиг

`addons/configs/vip/vip_weaponkit.ini` (при сборке в пакет не попадает, скопируйте файл `configs/vip/vip_weaponkit.ini` туда сами)

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `round_min` | `1` | с какого раунда выдавать кит |
| `roundlimit` | `3` | через сколько раундов можно снова выбрать кит |
| `autoopenmenu` | `1` | открывать меню само, если кит ещё не выбран, 1 да, 0 нет |
| `checksave` | `0` | 1 не выдавать кит, если игрок сохранил основное оружие с прошлого раунда |
| `groups_file` | `addons/configs/vip/groups.ini` | путь до groups.ini VIP Core, нужен чтобы взять WeaponKit прямо из группы |

Остальные секции это киты. Имя секции это id кита, `name` это название в меню, `team` для какой команды (0 для всех, 2 T, 3 CT), `weapon` что выдать, строк `weapon` может быть несколько.

<details>
<summary>Весь файл vip_weaponkit.ini</summary>

```
"WeaponKit"
{
    "round_min"         "1"   // минимум раундов для выдачи кита
    "roundlimit"        "3"   // через сколько раундов можно ещё раз выбрать кит
    "autoopenmenu"      "1"   // Открывать ли меню если ничего не выбрано
    "checksave"         "0"  // Проверять сейв оружия, 1 - не выдавать кит если игрок сейвнул основное оружие
    "groups_file"   "addons/configs/vip/groups.ini"   // подставь свой путь
    
    "ak_t" //имя для конфига 
    {
        "name"      "АК-47 + Броня"  // отображение в меню 
        "team"      "2"         // 0-для всех  2-T 3-CT
        "weapon"    "weapon_ak47"  //  https://totalcsgo.com/codes/give-codes
        "weapon"    "item_assaultsuit"
        "weapon"    "weapon_deagle"
    }
    
    "m4_ct"
    {
        "name"      "M4A4 + Броня"
        "team"      "3"
        "weapon"    "weapon_m4a1"
        "weapon"    "item_assaultsuit"
        "weapon"    "weapon_deagle"
    }
    
    "awp_all"
    {
        "name"      "AWP снайпер"
        "team"      "0"
        "weapon"    "weapon_awp"
        "weapon"    "item_assaultsuit"
        "weapon"    "weapon_flashbang"
        "weapon"    "weapon_flashbang"
        "weapon"    "weapon_glock"
    }

    "p90_all"
    {
        "name"      "P90 раш"
        "team"      "0"
        "weapon"    "weapon_p90"
        "weapon"    "item_assaultsuit"
        "weapon"    "weapon_hkp2000"
    }
}
```

</details>

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
