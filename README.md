<h1 align=center><code>VIP Modules</code></h1>

<div align=center>
  <img src=https://img.shields.io/badge/Counter--Strike%202-Metamod%202.0%20(KHook)-orange?style=flat-square alt=metamod>
  <a href=https://github.com/Cookies2122/vip-modules/commits><img src=https://img.shields.io/github/last-commit/Cookies2122/vip-modules?style=flat-square alt="last commit"></a>
  <a href=LICENSE><img src=https://img.shields.io/github/license/Cookies2122/vip-modules?style=flat-square alt=license></a>
</div>
<br>

Модули для [VIP Core](https://github.com/Pisex/cs2-vip) на Counter-Strike 2. Здесь мои модули и модули Pisex и ABKAM, перенесённые на новый SDK и Metamod 2.0. Все модули работают на Metamod 2.0 (KHook).

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

Если модулю нужно что-то ещё, это написано в его разделе.

## Установка

1. Соберите модуль (раздел [Сборка](#сборка)).
2. Скопируйте содержимое `build/package` в папку `csgo` на сервере. Там лежат `addons/vip_modules/<модуль>.so`, `addons/metamod/<модуль>.vdf` и конфиг модуля в `addons/configs/vip/`, если он есть.
3. Допишите ключи модуля в нужную группу в `addons/configs/vip/groups.ini`.
4. Допишите фразы модуля в `addons/translations/vip.phrases.txt`, внутрь блока `"Phrases"`.
5. Перезапустите сервер или смените карту.

Ключи пишутся внутрь группы, например:

```
"VIP"
{
	"server_id"	"1"

	"VIP"
	{
		"antiflash"	"3"
		"bhop"		"1"
		"health"	"120"
		"respawn"	"2"
	}
}
```

## Список модулей

**Мои модули**

| Модуль | Что делает | Ключи в groups.ini | Автор |
| --- | --- | --- | --- |
| [[VIP] Infinite Ammo](#vip-infinite-ammo) | Держит запас патронов у оружия VIP игрока на нужном уровне. Можно сделать бесконечные патроны или просто больше запаса, чем обычно. | `InfiniteReserveAmmo` | [\_ded\_cookies](https://github.com/Cookies2122) |
| [[VIP] Respawn++](#vip-respawn) | Расширенный респавн: возрождение по команде и автореспавн после смерти. Есть лимиты по времени раунда, по числу игроков и по числу живых. | `respawn` | [\_ded\_cookies](https://github.com/Cookies2122) и E!N |
| [[VIP] Weapon Kit](#vip-weapon-kit) | VIP игрок выбирает себе набор оружия (кит) в меню, и в начале раунда получает его. | `WeaponKit`, `WeaponkitMenu` | [\_ded\_cookies](https://github.com/Cookies2122) |
| [[VIP] Reserved slots](#vip-reserved-slots) | Резервные слоты для VIP. Когда обычные слоты заняты, обычный игрок не зайдёт, а VIP зайдёт. Если нужно, плагин освобождает место для VIP. | нет | [\_ded\_cookies](https://github.com/Cookies2122) |
| [[VIP] Regen Ammo](#vip-regen-ammo) | Пополняет патроны в оружии, пока оно не в руках. | `RegenAmmunition`, `DelayRegenAmmunition` | [\_ded\_cookies](https://github.com/Cookies2122) |

**Модули Pisex и ABKAM**

| Модуль | Что делает | Ключи в groups.ini | Автор |
| --- | --- | --- | --- |
| [VIP_AntiFlash](#vip_antiflash) | VIP игрока не слепят флешки. Можно выбрать, какие именно. | `antiflash` | [Pisex](https://github.com/Pisex) |
| [VIP_AwpManager](#vip_awpmanager) | Меняет число патронов в магазине AWP у VIP игрока. | `awp_manager` | [Pisex](https://github.com/Pisex) |
| [VIP_BaseFunctions](#vip_basefunctions) | При возрождении выдаёт VIP игроку здоровье, броню, шлем, дефьюзер и деньги. | `health`, `armor`, `helmet`, `money`, `defuser` | [Pisex](https://github.com/Pisex) |
| [VIP_Bhop](#vip_bhop) | Распрыжка (bhop) для VIP игрока. | `bhop` | [Pisex](https://github.com/Pisex) |
| [VIP_BuyTeamWeapon](#vip_buyteamweapon) | VIP игрок может купить оружие команды противника прямо из чата, например АК за CT. | `btw` | [Pisex](https://github.com/Pisex) |
| [VIP_DuckSpeed](#vip_duckspeed) | Быстрое приседание для VIP игрока. | `duckspeed` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Endurance](#vip_endurance) | VIP игрок не замедляется, когда в него попадают. | `Endurance` | [Pisex](https://github.com/Pisex) |
| [VIP_FOV](#vip_fov) | VIP игрок выбирает себе угол обзора (FOV) в меню. | `FOV` | [Pisex](https://github.com/Pisex) |
| [VIP_FastDefuse](#vip_fastdefuse) | VIP игрок быстрее разминирует бомбу. | `fd` | [Pisex](https://github.com/Pisex) |
| [VIP_FastPlant](#vip_fastplant) | VIP игрок быстрее ставит бомбу. | `fp` | [Pisex](https://github.com/Pisex) |
| [VIP_Fortnite_Hits](#vip_fortnite_hits) | Даёт VIP игроку цифры урона в стиле Fortnite из плагина Fortnite Hits. | `fortnite_hits` | [Pisex](https://github.com/Pisex) |
| [VIP_Gravity](#vip_gravity) | Меняет гравитацию VIP игрока. | `gravity` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Healthshot](#vip_healthshot) | Каждый раунд выдаёт VIP игроку шприцы. | `healthshot` | [Pisex](https://github.com/Pisex) |
| [VIP_Items](#vip_items) | В начале раунда выдаёт VIP игроку оружие и предметы. | `items` | [Pisex](https://github.com/Pisex) |
| [VIP_JoinSound](#vip_joinsound) | Когда VIP заходит на сервер, всем игрокам играет звук. | `JoinSound` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Jumps](#vip_jumps) | Дополнительные прыжки в воздухе. | `jumps` | [Pisex](https://github.com/Pisex) и [ABKAM](https://github.com/ABKAM2023) |
| [VIP_KillScreen](#vip_killscreen) | При убийстве у VIP игрока на экране мелькает цветной эффект. | `killscreen` | [Pisex](https://github.com/Pisex) |
| [VIP_MultiTest](#vip_multitest) | Тестовый VIP с выбором группы. Игрок пишет `!testvip` и в меню выбирает, какую группу попробовать. | нет | [Pisex](https://github.com/Pisex) |
| [VIP_NoFallDamage](#vip_nofalldamage) | VIP игрок не получает урон от падения. | `nofalldamage` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Penis](#vip_penis) | Шуточный модуль: вешает модель на VIP игрока. | `penis`, `penis_model` | [Pisex](https://github.com/Pisex) |
| [VIP_RainbowModel](#vip_rainbowmodel) | Модель VIP игрока переливается цветами. | `rainbow_model` | [Pisex](https://github.com/Pisex) |
| [VIP_RegenArmor](#vip_regenarmor) | Восстанавливает броню VIP игрока после урона. | `RegenArmor`, `DelayRegenArmor`, `IntervalRegenArmor` | [Pisex](https://github.com/Pisex) |
| [VIP_RegenHP](#vip_regenhp) | Восстанавливает здоровье VIP игрока после урона. | `RegenHP`, `DelayRegenHP`, `IntervalRegenHP` | [Pisex](https://github.com/Pisex) |
| [VIP_ResetDeaths](#vip_resetdeaths) | VIP игрок может обнулить себе смерти или убийства. | `ResetDeaths` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Respawn](#vip_respawn) | VIP игрок может возродиться командой `!respawn`. | `respawn` | [Pisex](https://github.com/Pisex) |
| [VIP_ShowDamage](#vip_showdamage) | Показывает VIP игроку, сколько урона он нанёс. | `show_damage` | [Pisex](https://github.com/Pisex) |
| [VIP_Skins](#vip_skins) | VIP игрок выбирает себе модель персонажа в меню. | `Skins` | [Pisex](https://github.com/Pisex) |
| [VIP_Smoke](#vip_smoke) | Цветной дым у дымовых гранат VIP игрока. | `smoke_color` | [Pisex](https://github.com/Pisex) |
| [VIP_Speed](#vip_speed) | Меняет скорость бега VIP игрока. | `speed` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Tag](#vip_tag) | Клан-тег VIP игрока в таблице счёта (TAB). | `clantag` | [Pisex](https://github.com/Pisex) |
| [VIP_TeammatesHeal](#vip_teammatesheal) | VIP игрок лечит союзников, когда стреляет в них. | `heal_teammates` | [ABKAM](https://github.com/ABKAM2023) |
| [VIP_Test](#vip_test) | Тестовый VIP: игрок пишет `!viptest` и получает группу на время. | нет | [Pisex](https://github.com/Pisex) |
| [VIP_Time](#vip_time) | В заданное время выдаёт VIP группу всем игрокам, например ночью. | нет | [Pisex](https://github.com/Pisex) |
| [VIP_Vampirism](#vip_vampirism) | VIP игрок получает здоровье за урон по врагу. | `Vampirism` | [Pisex](https://github.com/Pisex) |
| [VIP_Vips](#vip_vips) | Команда `!vips` показывает список VIP игроков на сервере. | нет | [Pisex](https://github.com/Pisex) |

## Мои модули

### [VIP] Infinite Ammo

Держит запас патронов у оружия VIP игрока на нужном уровне. Можно сделать бесконечные патроны или просто больше запаса, чем обычно.

**groups.ini**

```
"InfiniteReserveAmmo"  "premium"
```

| Ключ | Что значит |
| --- | --- |
| `InfiniteReserveAmmo` | имя пака из vip_infiniteammo.ini |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"InfiniteReserveAmmo"
{
	"en"		"Infinite reserve ammo"
	"ru"		"Бесконечные патроны"
}
```

**Конфиг**

`addons/configs/vip/vip_infiniteammo.ini` (при сборке в пакет не попадает, скопируйте файл `configs/vip/vip_infiniteammo.ini` туда сами)

Каждая секция в конфиге это пак. В паке `default` задаёт запас для оружия, которого нет в списке, а `weapon_...` задаёт запас для конкретного оружия. Пак `god` со значением 999 это по сути бесконечные патроны.

<details>
<summary>Весь файл vip_infiniteammo.ini</summary>

```
"InfiniteReserveAmmo"
{
	// ===========================================
	// Пак "god" - бесконечные обоймы
	// ===========================================
	"god"
	{
		"default"					"999"
	}

	// ===========================================
	// Пак "premium" - двойной запас от дефолта
	// ===========================================
	"premium"
	{
		"default"					"6" // Для оружия ели нету в списке

		// ===== Пистолеты =====
		"weapon_glock"				"6"
		"weapon_hkp2000"			"6"
		"weapon_usp_silencer"		"6"
		"weapon_elite"				"4"
		"weapon_p250"				"6"
		"weapon_fiveseven"			"4"
		"weapon_tec9"				"6"
		"weapon_cz75a"				"4"
		"weapon_deagle"				"6"
		"weapon_revolver"			"4"

		// ===== Дробовики =====
		"weapon_nova"				"6"
		"weapon_sawedoff"			"6"
		"weapon_mag7"				"4"
		"weapon_xm1014"			"6"

		// ===== ПП =====
		"weapon_mac10"				"4"
		"weapon_mp9"				"4"
		"weapon_mp7"				"6"
		"weapon_mp5sd"				"4"
		"weapon_ump45"				"6"
		"weapon_p90"				"6"
		"weapon_bizon"				"6"

		// ===== Винтовки =====
		"weapon_galilar"			"6"
		"weapon_famas"				"6"
		"weapon_ak47"				"6"
		"weapon_m4a1"				"8"
		"weapon_m4a1_silencer"		"6"
		"weapon_sg556"				"6"
		"weapon_aug"				"6"

		// ===== Снайперские =====
		"weapon_ssg08"				"4"
		"weapon_awp"				"4"
		"weapon_g3sg1"				"4"
		"weapon_scar20"				"4"

		// ===== Пулемёты =====
		"weapon_m249"				"4"
		"weapon_negev"				"4"
	}

	// ===========================================
	// Пак "standart" - дефолтные значения из обновы 19.03.2026
	// Значения - количество ОБОЙМ в резерве
	// ===========================================
	"standart"
	{
		"default"					"3" // Для оружия ели нету в списке

		// ===== ПИСТОЛЕТЫ =====
		"weapon_glock"				"3"			// 20 × 3
		"weapon_hkp2000"			"3"			// 13 × 3
		"weapon_usp_silencer"		"3"			// 12 × 3
		"weapon_elite"				"2"			// 30 × 2
		"weapon_p250"				"3"			// 13 × 3
		"weapon_fiveseven"			"2"			// 20 × 2
		"weapon_tec9"				"3"			// 18 × 3
		"weapon_cz75a"				"2"			// 12 × 2
		"weapon_deagle"				"3"			// 7 × 3
		"weapon_revolver"			"2"			// 8 × 2

		// ===== ДРОБОВИКИ =====
		"weapon_nova"				"3"			// 8 × 3
		"weapon_sawedoff"			"3"			// 7 × 3
		"weapon_mag7"				"2"			// 5 × 2
		"weapon_xm1014"			"3"			    // 7 × 3

		// ===== ПП =====
		"weapon_mac10"				"2"			// 30 × 2
		"weapon_mp9"				"2"			// 30 × 2
		"weapon_mp7"				"3"			// 30 × 3
		"weapon_mp5sd"				"2"			// 30 × 2
		"weapon_ump45"				"3"			// 25 × 3
		"weapon_p90"				"3"			// 50 × 3
		"weapon_bizon"				"3"			// 64 × 3

		// ===== ВИНТОВКИ =====
		"weapon_galilar"			"3"			// 35 × 3
		"weapon_famas"				"3"			// 25 × 3
		"weapon_ak47"				"3"			// 30 × 3
		"weapon_m4a1"				"4"			// 30 × 4
		"weapon_m4a1_silencer"		"3"			// 25 × 3
		"weapon_sg556"				"3"			// 30 × 3
		"weapon_aug"				"3"			// 30 × 3

		// ===== СНАЙПЕРСКИЕ =====
		"weapon_ssg08"				"2"			// 10 × 2
		"weapon_awp"				"2"			// 5 × 2
		"weapon_g3sg1"				"2"			// 20 × 2
		"weapon_scar20"				"2"			// 20 × 2

		// ===== ПУЛЕМЁТЫ =====
		"weapon_m249"				"2"			// 100 × 2
		"weapon_negev"				"2"			// 150 × 2
	}
}
```

</details>

### [VIP] Respawn++

Расширенный респавн: возрождение по команде и автореспавн после смерти. Есть лимиты по времени раунда, по числу игроков и по числу живых.

**groups.ini**

```
"respawn"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `respawn` | доступ к респавну, 1 включено, 0 нет |

Не ставьте вместе с VIP_Respawn: у них один ключ `respawn` и одинаковое имя файла `vip_respawn.so`.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!respawn` | возродиться (также `respawn`, в консоли `mm_respawn` и `sm_respawn`) |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"RespawnAvailable"
{
	"en"		"Respawns available: %d"
	"ru"		"Респавнов доступно: %d"
}
"RespawnRemaining"
{
	"en"		"Respawns remaining: %d"
	"ru"		"Респавнов осталось: %d"
}
"RespawnIsNotAvailable"
{
	"en"		"Respawn is unavailable."
	"ru"		"Респавн недоступен."
}
"RespawnIsNoLongerAvailable"
{
	"en"		"Respawn is no longer available."
	"ru"		"Респавн больше недоступен."
}
"AutoRespawnIsNoLongerAvailable"
{
	"en"		"Autorespawn is no longer available."
	"ru"		"Автореспавн больше недоступен."
}
"NotEnoughOnlinePlayersForRespawn"
{
	"en"		"Not enough players online to respawn"
	"ru"		"Недостаточно игроков онлайн для респавна"
}
"NotEnoughOnlinePlayersForAutoRespawn"
{
	"en"		"Not enough players online for auto-respawn"
	"ru"		"Недостаточно игроков онлайн для автореспавна"
}
"RespawnBlockedMinAlive"
{
	"en"		"Respawn blocked: not enough alive players!"
	"ru"		"Респавн заблокирован: слишком мало живых игроков!"
}
```

Фразы `respawn`, `Prefix`, `LimitRespawn`, `SelectTeam`, `YourAlive` уже есть в vip.phrases.txt ядра.

**Конфиг**

`addons/configs/vip/vip_respawn.ini` (при сборке в пакет не попадает, скопируйте файл `configs/vip/vip_respawn.ini` туда сами)

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `RespawnEnhanced` | `3` | сколько респавнов за раунд, обычные и авто считаются вместе |
| `AutoRespawn` | `1` | доступ к автореспавну, 1 да, 0 нет |
| `NoRespawnDelay` | `40` | через сколько секунд после начала раунда респавн по команде закрывается |
| `NoAutoRespawnDelay` | `35` | через сколько секунд после начала раунда закрывается автореспавн |
| `RespawnDelay` | `7` | через сколько секунд после смерти можно возродиться командой |
| `AutoRespawnDelay` | `3` | через сколько секунд после смерти сработает автореспавн |
| `RespawnMinPlayers` | `2` | сколько минимум игроков нужно для респавна по команде |
| `AutoRespawnMinPlayers` | `5` | сколько минимум игроков нужно для автореспавна |
| `HPAfterRespawn` | `75` | здоровье после респавна по команде |
| `HPAfterAutoRespawn` | `50` | здоровье после автореспавна |
| `MinAliveMode` | `2` | кого считать для MinAlive: 0 своя команда, 1 команда противника, 2 обе |
| `MinAlive` | `2` | если живых столько или меньше, респавн запрещён, 0 выключено |

```
"VIP_Respawn"
{
    "RespawnEnhanced"        "3"     // Кол-во респавнов (учитывается как обычных, так и авто).
    "AutoRespawn"            "1"     // Доступ к автореспавну
    "NoRespawnDelay"         "40"    // Через сколько сек. респавн будет недоступен до след. раунда
    "NoAutoRespawnDelay"     "35"    // Через сколько сек. автореспавн будет недоступен до след. раунда
    "RespawnDelay"           "7"     // Через сколько сек. после смерти респавн будет доступен
    "AutoRespawnDelay"       "3"     // Через сколько сек. после смерти произойдет автореспавн
    "RespawnMinPlayers"      "2"     // Сколько мин. игроков нужно для работы респавна
    "AutoRespawnMinPlayers"  "5"     // Сколько мин. игроков нужно для работы автореспавна
    "HPAfterRespawn"         "75"    // Кол-во здоровья после респавна
    "HPAfterAutoRespawn"     "50"    // Кол-во здоровья после автореспавна
    "MinAliveMode"           "2"     // Режим проверки 0 - своя команда 1 - вражеская 2 - обе
    "MinAlive"               "2"     // Если живых этого числа - респавн заблокирован (0 - выкл)
}
```

### [VIP] Weapon Kit

VIP игрок выбирает себе набор оружия (кит) в меню, и в начале раунда получает его.

**groups.ini**

```
"WeaponKit"      "all"
"WeaponkitMenu"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `WeaponKit` | `all` все киты, или id китов через запятую, например `ak_t,awp_all` |
| `WeaponkitMenu` | пункт в меню VIP для выбора кита |

**Команды**

| Команда | Что делает |
| --- | --- |
| `!wkit` | открыть выбор кита |
| `!weaponkit` | то же самое |

**vip.phrases.txt**

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

**Конфиг**

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

### [VIP] Reserved slots

Резервные слоты для VIP. Когда обычные слоты заняты, обычный игрок не зайдёт, а VIP зайдёт. Если нужно, плагин освобождает место для VIP.

**Конфиг**

`addons/configs/vip/vip_reserved_slots.ini` (при сборке в пакет не попадает, скопируйте файл `configs/vip/vip_reserved_slots.ini` туда сами)

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `public_slots` | `6` | сколько игроков без VIP может быть на сервере одновременно |
| `reserve_slots` | `0` | сколько слотов держать под VIP, если не задан public_slots |
| `vip_groups` | пусто | какие VIP группы пускать в резерв, через `;`, пусто для всех |
| `evict_nonvip` | `0` | 1 кикать одного игрока без VIP, когда VIP заходит на полный сервер, 0 никого не трогать |
| `kick_random` | `0` | кого кикать: 0 первого по слоту, 1 случайного |
| `kick_reason_id` | `135` | причина отключения, 135 это "сервер заполнен" |

Задайте что-то одно: `public_slots` или `reserve_slots`, второе посчитается от maxplayers сервера. Если заданы оба, берётся `public_slots`. Если оба 0, под VIP уходит 2 слота.

<details>
<summary>Весь файл vip_reserved_slots.ini</summary>

```
"ReservedSlots"
{
	// =====================================================================
	//  Можно задать ОДНО из двух полей второе считается автоматически из maxplayers сервера
	//
	//   public_slots    лимит на одновременное число НЕ-VIP игроков
	//   reserve_slots   сколько слотов держать под VIP (maxplayers - public)
	//   maxplayers      указывается в параметрах запуска самого сервера на сайте плагин сам подменит на нужный слот например 10/6 на сервере
	//
	//  Примеры
	//
	//   maxplayers=10, public_slots=6    6 общих + 4 под VIP
	//   maxplayers=20, reserve_slots=4   16 общих + 4 под VIP
	//   maxplayers=12, оба=0             авто (maxplayers - 2) 10 общих + 2 VIP
	//
	//  Если оба заданы берётся public_slots, reserve_slots игнорируется
	// =====================================================================
	"public_slots"     "6"
	"reserve_slots"    "0"

	"vip_groups"       "" 		// Список VIP-групп через ';' можно пусто для всех
	"evict_nonvip"     "0" 		// 1 - когда VIP заходит на ПОЛНОСТЬЮ занятый сервер плагин кикнет одного не VIP, 0 - никого не выгоняем

	"kick_random"      "0" 		// 0 - кикать первого по slot, 1 - случайного
	"kick_reason_id"   "135" 	// ID причины дисконнекта (сервер заполнен)
}
```

</details>

### [VIP] Regen Ammo

Пополняет патроны в оружии, пока оно не в руках.

> Старая версия. На новый SDK и Metamod 2.0 этот модуль пока не переносился и лежит как был.

**groups.ini**

```
"RegenAmmunition"       "2"
"DelayRegenAmmunition"  "10"
```

| Ключ | Что значит |
| --- | --- |
| `RegenAmmunition` | сколько патронов добавлять за раз |
| `DelayRegenAmmunition` | раз в сколько секунд добавлять |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"DelayRegenAmmunition"
{
	"en"		"Ammo regeneration"
	"ru"		"Реген патронов"
}
```

## Модули Pisex и ABKAM

Оригиналы лежат в [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules). Что поменялось в этих модулях:

- Переведено на новый SDK ([Wend4r/sourcesdk](https://github.com/Wend4r/sourcesdk)), старый после обновления CS2 от 12.11.2026 уже не подходит.
- Работает только на Metamod 2.0 (KHook), старый Metamod на SourceHook больше не поддерживается.
- Заголовки Utils обновлены под текущую версию, имена интерфейсов теперь `UTILS_INTERFACE` и `MENUS_INTERFACE`.
- Своя функция `GameEntitySystem()` убрана, в новом SDK entity system берётся через `IGameResourceService`.
- SchemaEntity обновлена: актуальные оффсеты виртуальных функций.
- Часть модулей при выгрузке удаляла интерфейсы VIP Core и Utils (`delete g_pVIPCore`), из-за этого сервер мог упасть при `meta unload`. Это убрано.
- VIP_BaseFunctions: броня регистрировалась под ключом `defuser`, теперь ключ `armor` работает как надо.
- VIP_Skins, VIP_BuyTeamWeapon, VIP_Time и VIP_Vips: конфиг теперь кладётся в пакет при сборке.
- VIP_Endurance и VIP_RainbowModel: хук GameFrame переписан на KHook. В VIP_FastDefuse и VIP_FastPlant убрано объявление хука, который нигде не ставился.

### VIP_AntiFlash

VIP игрока не слепят флешки. Можно выбрать, какие именно.

**groups.ini**

```
"antiflash"  "3"
```

| Ключ | Что значит |
| --- | --- |
| `antiflash` | режим, смотрите таблицу ниже |

| Значение | Что будет |
| --- | --- |
| `1` | не слепят флешки тиммейтов |
| `2` | не слепят свои флешки |
| `3` | не слепят свои флешки и флешки тиммейтов |
| `4` | не слепят никакие флешки |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"antiflash"
{
	"en"		"Anti-Flash"
	"ru"		"Антифлеш"
}
```

### VIP_AwpManager

Меняет число патронов в магазине AWP у VIP игрока.

**groups.ini**

```
"awp_manager"  "10"
```

| Ключ | Что значит |
| --- | --- |
| `awp_manager` | сколько патронов в магазине |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"awp_manager"
{
	"en"		"AWP Manager"
	"ru"		"AWP Manager"
}
```

### VIP_BaseFunctions

При возрождении выдаёт VIP игроку здоровье, броню, шлем, дефьюзер и деньги.

**groups.ini**

```
"health"   "120"
"armor"    "100"
"helmet"   "1"
"money"    "++1000"
"defuser"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `health` | здоровье |
| `armor` | броня |
| `helmet` | шлем, 1 выдать, 0 нет |
| `money` | деньги |
| `defuser` | дефьюзер, 1 выдать, 0 нет |

Для `health`, `armor` и `money` можно писать просто число, например `"120"`, тогда будет ровно столько. Если написать `"++30"`, то 30 прибавится к текущему значению.

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"health"
{
	"en"		"Health"
	"ru"		"Здоровье"
}
"armor"
{
	"en"		"Armor"
	"ru"		"Броня"
}
"helmet"
{
	"en"		"Helmet"
	"ru"		"Шлем"
}
"money"
{
	"en"		"Cash"
	"ru"		"Деньги"
}
"defuser"
{
	"en"		"Defuser"
	"ru"		"Дефуза"
}
```

**Конфиг**

`addons/configs/vip/vip_bf.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `round_min` | `1` | с какого раунда работает модуль: 0 всегда, 1 все раунды кроме пистолетных, больше 1 с этого раунда (пистолетные пропускаются) |

```
"VIP"
{
    "round_min"     "1"     //Только после первого раунда будут возможности модуля
}
```

### VIP_Bhop

Распрыжка (bhop) для VIP игрока.

**groups.ini**

```
"bhop"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `bhop` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"bhop"
{
	"en"		"Bhop"
	"ru"		"Бхоп"
}
```

### VIP_BuyTeamWeapon

VIP игрок может купить оружие команды противника прямо из чата, например АК за CT.

**groups.ini**

```
"btw"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `btw` | доступ, 1 да, 0 нет |

Купить можно только в зоне закупки и если хватает денег. В меню VIP этого пункта нет, поэтому фраза `btw` не нужна.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!<название>` | купить оружие из конфига, например `!ak47` за CT или `!m4a1` за T. В консоли `mm_<название>` |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"btw_round_start"
{
	"en"		"The purchase of opposing team weapons is available to you: %s"
	"ru"		"Вам доступна покупка оружия команды противника: %s"
}
"btw_no_money"
{
	"en"		"Not enough money to buy a gun"
	"ru"		"Недостаточно денег для покупки оружия"
}
"btw_no_buyzone"
{
	"en"		"You can't buy a gun when you're not in the purchasing area"
	"ru"		"Вы не можете купить оружие, если вы не находитесь в зоне покупки"
}
```

**Конфиг**

`addons/configs/vip/vip_btw.ini`

Секция `CT` это то, что может купить CT, секция `T` то, что может купить T. Имя внутри секции это команда (`ak47` даёт `!ak47` и `mm_ak47`), `price` цена, `weapon` что выдать.

<details>
<summary>Весь файл vip_btw.ini</summary>

```
"VIP"
{
    "CT"
    {
        "ak47"  //!ak47 and mm_ak47
        {
            "price"     "2700"
            "weapon"    "weapon_ak47"
        }
    }
    "T"
    {
        "m4a1"  //!m4a1 and mm_m4a1
        {
            "price"     "2900"
            "weapon"    "weapon_m4a1_silencer"
        }
        "m4a4"  //!m4a4 and mm_m4a4
        {
            "price"     "3100"
            "weapon"    "weapon_m4a1"
        }
    }
}
```

</details>

### VIP_DuckSpeed

Быстрое приседание для VIP игрока.

**groups.ini**

```
"duckspeed"  "10.0"
```

| Ключ | Что значит |
| --- | --- |
| `duckspeed` | скорость приседания, чем больше, тем быстрее |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"duckspeed"
{
	"en"		"Fast Crouch"
	"ru"		"Быстрое приседание"
}
```

### VIP_Endurance

VIP игрок не замедляется, когда в него попадают.

**groups.ini**

```
"Endurance"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `Endurance` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"Endurance"
{
	"en"		"Endurance"
	"ru"		"Выносливость"
}
```

### VIP_FOV

VIP игрок выбирает себе угол обзора (FOV) в меню.

**groups.ini**

```
"FOV"  "100,90,80,70,60"
```

| Ключ | Что значит |
| --- | --- |
| `FOV` | варианты FOV через запятую, они будут в меню |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"FOV"
{
	"en"		"Viewing angle"
	"ru"		"Угол обзора"
}
"FOV_Title"
{
	"en"		"Select FOV"
	"ru"		"Выберите FOV"
}
```

### VIP_FastDefuse

VIP игрок быстрее разминирует бомбу.

**groups.ini**

```
"fd"  "50"
```

| Ключ | Что значит |
| --- | --- |
| `fd` | на сколько процентов быстрее |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"fd"
{
	"en"		"Fast Defuse"
	"ru"		"Быстрое обезвреживание"
}
```

### VIP_FastPlant

VIP игрок быстрее ставит бомбу.

**groups.ini**

```
"fp"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `fp` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"fp"
{
	"en"		"Fast Plant"
	"ru"		"Быстрая закладка бомбы"
}
```

### VIP_Fortnite_Hits

Даёт VIP игроку цифры урона в стиле Fortnite из плагина Fortnite Hits.

Дополнительно нужен [Fortnite Hits](https://github.com/Pisex/cs2-fortnite_hits).

**groups.ini**

```
"fortnite_hits"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `fortnite_hits` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"fortnite_hits"
{
	"en"		"Damage Display"
	"ru"		"Отображение урона"
}
```

### VIP_Gravity

Меняет гравитацию VIP игрока.

**groups.ini**

```
"gravity"  "0.8"
```

| Ключ | Что значит |
| --- | --- |
| `gravity` | 1.0 обычная, меньше прыжок выше, больше тяжелее, можно от 0.1 до 2.0 |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"gravity"
{
	"en"		"Gravity"
	"ru"		"Гравитация"
}
```

### VIP_Healthshot

Каждый раунд выдаёт VIP игроку шприцы.

**groups.ini**

```
"healthshot"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `healthshot` | сколько шприцев |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"healthshot"
{
	"en"		"Healthshots"
	"ru"		"Шприцы"
}
```

**Конфиг**

`addons/configs/vip/vip_healthshot.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `round_min` | `2` | с какого раунда выдавать шприцы |

```
"VIP"
{
    "round_min"     "2"     //Только со второго будут выданы шприцы
}
```

### VIP_Items

В начале раунда выдаёт VIP игроку оружие и предметы.

**groups.ini**

```
"items"  "weapon_ak47 weapon_flashbang"
```

| Ключ | Что значит |
| --- | --- |
| `items` | что выдать, через пробел |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"items"
{
	"en"		"Weapons at the start of a round"
	"ru"		"Оружие в начале раунда"
}
```

**Конфиг**

`addons/configs/vip/vip_items.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `round_min` | `2` | с какого раунда выдавать предметы |

```
"VIP"
{
    "round_min"     "2"     //С какого раунда выдавать предметы
}
```

### VIP_JoinSound

Когда VIP заходит на сервер, всем игрокам играет звук.

**groups.ini**

```
"JoinSound"  "sounds/music/vip_join.vsnd_c"
```

| Ключ | Что значит |
| --- | --- |
| `JoinSound` | путь к звуку |

Звук запускается у игроков командой `play`, поэтому файл должен быть у них: в самой игре или в аддоне сервера.

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"JoinSound"
{
	"en"		"Join Sound"
	"ru"		"Звук при подключении"
}
```

### VIP_Jumps

Дополнительные прыжки в воздухе.

**groups.ini**

```
"jumps"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `jumps` | сколько дополнительных прыжков |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"jumps"
{
	"en"		"Jumps"
	"ru"		"Прыжки"
}
```

### VIP_KillScreen

При убийстве у VIP игрока на экране мелькает цветной эффект.

**groups.ini**

```
"killscreen"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `killscreen` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"killscreen"
{
	"en"		"Kill Screen"
	"ru"		"Цветной экран убийства"
}
```

**Конфиг**

`addons/configs/vip/vip_ks.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `effect_time` | `0.7` | сколько секунд держится эффект |

```
"VIP"
{
    "effect_time"       "0.7"	//Время отображения эффекта(число с плавающей точкой)
}
```

### VIP_MultiTest

Тестовый VIP с выбором группы. Игрок пишет `!testvip` и в меню выбирает, какую группу попробовать.

Не ставьте вместе с VIP_Test: у них одинаковые команды и один файл `vip_test.ini`.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!testvip` | открыть меню тестового VIP |
| `!viptest` | то же самое |
| `mm_testvip` | то же из консоли, также `sm_testvip`, `mm_viptest`, `sm_viptest` |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"VIPTest_Title"
{
	"en"		"Choose a VIP group"
	"ru"		"Выберите вип группу"
}
```

Фразы `AlreadyVIP`, `AlreadyReceived`, `ReceivedDisabled` уже есть в vip.phrases.txt ядра.

**Конфиг**

`addons/configs/vip/vip_test.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `type` | `1` | 1 общий timeout: взял одну группу, другие нельзя, пока не пройдёт timeout. 2 у каждой группы свой timeout |

Остальные секции это группы. Имя секции это имя VIP группы, `display` название в меню, `time` на сколько секунд выдаётся, `timeout` через сколько секунд после окончания можно взять снова (0 только один раз).

```
"VIP"
{
    "type"      "1"     //Тип получения випки
                        //1 - Глобальный timeout, пример: игрок взял Example1 и не может взять Example2 пока не пройдет timeout
                        //2 - Timeout по группе, пример: игрок взял Example1 и после этого может взять Example2

    "Example1"    //Вип группа
    {
        "display"   "Lite-VIP"  //Отображаемое имени в меню
        "time"      "7200"      //Время выдачи випки в секундах
        "timeout"   "14400"     //Перезарядка между повторными получениями випки в секундах(0 - никогда)
    }
    "Example2"    //Вип группа
    {
        "display"   "VIP"       //Отображаемое имени в меню
        "time"      "3600"      //Время выдачи випки в секундах
        "timeout"   "14400"     //Перезарядка между повторными получениями випки в секундах(0 - никогда)
    }
}
```

### VIP_NoFallDamage

VIP игрок не получает урон от падения.

**groups.ini**

```
"nofalldamage"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `nofalldamage` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"nofalldamage"
{
	"en"		"No Fall Damage"
	"ru"		"Отключение урона от падения"
}
```

### VIP_Penis

Шуточный модуль: вешает модель на VIP игрока.

**groups.ini**

```
"penis"        "1"
"penis_model"  "models/kolka/penis/penis.vmdl"
```

| Ключ | Что значит |
| --- | --- |
| `penis` | 1 включено, 0 нет |
| `penis_model` | путь к модели |

Модель должна быть в аддоне сервера и в прекеше, например через [ResourcePrecacher](https://github.com/Pisex/ResourcePrecacher). Модели из оригинала: `models/kolka/penis/penis_weapon.vmdl`, `penis_small.vmdl`, `penis_medium.vmdl`, `penis.vmdl`.

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"penis"
{
	"en"		"Penis"
	"ru"		"Пенис"
}
```

### VIP_RainbowModel

Модель VIP игрока переливается цветами.

**groups.ini**

```
"rainbow_model"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `rainbow_model` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"rainbow_model"
{
	"en"		"Rainbow model"
	"ru"		"Разноцветная модель"
}
```

### VIP_RegenArmor

Восстанавливает броню VIP игрока после урона.

**groups.ini**

```
"RegenArmor"          "10"
"DelayRegenArmor"     "5"
"IntervalRegenArmor"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `RegenArmor` | сколько брони за раз |
| `DelayRegenArmor` | через сколько секунд после урона начать |
| `IntervalRegenArmor` | раз в сколько секунд |

С примером выше через 5 секунд после урона броня растёт на 10 каждые 2 секунды. Максимум 100 или значение `armor` из VIP_BaseFunctions.

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"RegenArmor"
{
	"en"		"Regen Armor"
	"ru"		"Реген Брони"
}
```

### VIP_RegenHP

Восстанавливает здоровье VIP игрока после урона.

**groups.ini**

```
"RegenHP"          "10"
"DelayRegenHP"     "5"
"IntervalRegenHP"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `RegenHP` | сколько HP за раз |
| `DelayRegenHP` | через сколько секунд после урона начать |
| `IntervalRegenHP` | раз в сколько секунд |

С примером выше через 5 секунд после урона здоровье растёт на 10 каждые 2 секунды, до максимального здоровья игрока.

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"RegenHP"
{
	"en"		"Regen HP"
	"ru"		"Реген ХП"
}
```

### VIP_ResetDeaths

VIP игрок может обнулить себе смерти или убийства.

**groups.ini**

```
"ResetDeaths"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `ResetDeaths` | 1 доступ есть, 0 нет |

**Команды**

| Команда | Что делает |
| --- | --- |
| `!rd` | обнулить смерти (также `rd`, `mm_rd`, `sm_rd`) |
| `!rs` | обнулить убийства (также `rs`, `mm_rs`, `sm_rs`) |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"ResetDeaths"
{
	"en"		"Reset deaths"
	"ru"		"Сброс смертей"
}
"deaths_reset"
{
	"en"		"Your deaths have been reset!"
	"ru"		"Ваши смерти были сброшены!"
}
"deaths_already_zero"
{
	"en"		"Your deaths are already zero."
	"ru"		"Ваши смерти уже равны нулю."
}
"kills_already_zero"
{
	"en"		"Your kills are already zero."
	"ru"		"Ваши убийства уже равны нулю."
}
"kills_reset"
{
	"en"		"Your kills have been reset!"
	"ru"		"Ваши убийства были сброшены!"
}
```

Фразы `NotAccess` уже есть в vip.phrases.txt ядра.

### VIP_Respawn

VIP игрок может возродиться командой `!respawn`.

**groups.ini**

```
"respawn"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `respawn` | сколько раз за раунд |

Не ставьте вместе с [VIP] Respawn++: у них один ключ `respawn` и одинаковое имя файла `vip_respawn.so`.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!respawn` | возродиться (также `respawn`, в консоли `mm_respawn` и `sm_respawn`) |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"respawn"
{
	"en"		"Respawn"
	"ru"		"Респавн"
}
```

Фразы `EndRound`, `LimitRespawn`, `SelectTeam`, `YourAlive` уже есть в vip.phrases.txt ядра.

### VIP_ShowDamage

Показывает VIP игроку, сколько урона он нанёс.

**groups.ini**

```
"show_damage"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `show_damage` | 1 включено, 0 нет |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"show_damage"
{
	"en"		"Show damage"
	"ru"		"Показ урона"
}
```

### VIP_Skins

VIP игрок выбирает себе модель персонажа в меню.

**groups.ini**

```
"Skins"  "1,2"
```

| Ключ | Что значит |
| --- | --- |
| `Skins` | id скинов из vip_skins.ini через запятую или пробел |

Модели должны быть на сервере и в прекеше, например через [ResourcePrecacher](https://github.com/Pisex/ResourcePrecacher).

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"Skins"
{
	"en"		"Skins"
	"ru"		"Скины"
}
"Disable_Skin"
{
	"en"		"Disable skin"
	"ru"		"Отключить скин"
}
"Select_Skin"
{
	"en"		"Select skin"
	"ru"		"Выберите скин"
}
"Cooldown"
{
	"en"		"The choice will become available in %i seconds"
	"ru"		"Выбор станет доступным через %i сек"
}
```

**Конфиг**

`addons/configs/vip/vip_skins.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `time` | `2` | через сколько секунд после возрождения ставить модель |
| `cooldown` | `30` | сколько секунд ждать между сменами скина |

Остальные секции это скины. Имя секции это id, `name` название в меню, `model_ct` модель за CT, `model_t` модель за T.

```
"Skins"
{
	"time"		"2"
	"cooldown"	"30"

	"1"
	{
		"name"		"SAS / Phoenix"
		"model_ct"	"characters/models/ctm_sas/ctm_sas.vmdl"
		"model_t"	"characters/models/tm_phoenix/tm_phoenix.vmdl"
	}
}
```

### VIP_Smoke

Цветной дым у дымовых гранат VIP игрока.

**groups.ini**

```
"smoke_color"  "random"
```

| Ключ | Что значит |
| --- | --- |
| `smoke_color` | `random` случайный цвет, или цвет RGB через пробел, например `255 0 0` |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"smoke_color"
{
	"en"		"Colored smoke"
	"ru"		"Цветной смок"
}
```

### VIP_Speed

Меняет скорость бега VIP игрока.

**groups.ini**

```
"speed"  "1.1"
```

| Ключ | Что значит |
| --- | --- |
| `speed` | 1.0 обычная, 1.1 немного быстрее, можно от 0.1 до 2.0 |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"speed"
{
	"en"		"Speed"
	"ru"		"Скорость"
}
```

### VIP_Tag

Клан-тег VIP игрока в таблице счёта (TAB).

**groups.ini**

```
"clantag"  "[VIP]"
```

| Ключ | Что значит |
| --- | --- |
| `clantag` | текст тега |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"clantag"
{
	"en"		"Clan Tag"
	"ru"		"Клан-Тег"
}
```

### VIP_TeammatesHeal

VIP игрок лечит союзников, когда стреляет в них.

**groups.ini**

```
"heal_teammates"  "50"
```

| Ключ | Что значит |
| --- | --- |
| `heal_teammates` | сколько процентов от урона вернётся союзнику здоровьем |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"heal_teammates"
{
	"en"		"Heal Teammates"
	"ru"		"Лечение союзников"
}
```

**Конфиг**

`addons/configs/vip/teammates_heal.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `syringe_effect` | `1` | эффект шприца, 1 включить, 0 выключить |
| `effect_time` | `1.2` | сколько секунд длится эффект |
| `weapon_blacklist` | `weapon_molotov;weapon_hegrenade;` | оружие, которым лечить нельзя, через `;` |
| `max_shot_hp` | `50` | максимум HP за один выстрел |

```
"VIP_Teammates_Heal"
{
    "syringe_effect"     "1"     // Эффект шприца 0 - Выключить, 1 - Включить
    "effect_time"        "1.2"   // Длительность эффекта шприца
    "weapon_blacklist"   "weapon_molotov;weapon_hegrenade;" // Список запрещенного оружия
    "max_shot_hp"        "50"    // Максимальное количество хп, которое можно восстановить за выстрел
}
```

### VIP_Test

Тестовый VIP: игрок пишет `!viptest` и получает группу на время.

Не ставьте вместе с VIP_MultiTest: у них одинаковые команды и один файл `vip_test.ini`.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!viptest` | получить тестовый VIP |
| `!testvip` | то же самое |
| `mm_viptest` | то же из консоли, также `sm_viptest`, `mm_testvip`, `sm_testvip` |

**vip.phrases.txt**

Фразы `AlreadyVIP`, `AlreadyReceived`, `ReceivedDisabled` уже есть в vip.phrases.txt ядра.

**Конфиг**

`addons/configs/vip/vip_test.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `group` | `VIP` | какую VIP группу выдавать |
| `time` | `60` | на сколько секунд |
| `timeout` | `0` | через сколько секунд после окончания можно взять снова, 0 только один раз |

```
"VIP"
{
    "group"     "VIP"
    "time"      "60"
    "timeout"   "0"
}
```

### VIP_Time

В заданное время выдаёт VIP группу всем игрокам, например ночью.

Время проверяется раз в минуту. Группа выдаётся только тем, у кого VIP нет, в базу не сохраняется и снимается, когда время закончилось.

**Конфиг**

`addons/configs/vip/vip_time.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `group` | `VIP` | какую VIP группу выдавать |
| `start_time` | `22:00` | с какого времени, часы:минуты |
| `end_time` | `08:00` | до какого времени, можно через полночь |

```
"VIP"
{
	"group"		"VIP"
	"start_time"	"22:00"
	"end_time"	"08:00"
}
```

### VIP_Vampirism

VIP игрок получает здоровье за урон по врагу.

**groups.ini**

```
"Vampirism"  "10"
```

| Ключ | Что значит |
| --- | --- |
| `Vampirism` | сколько процентов от урона вернётся здоровьем |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"Vampirism"
{
	"en"		"Vampirism"
	"ru"		"Вампиризм"
}
```

### VIP_Vips

Команда `!vips` показывает список VIP игроков на сервере.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!vips` | список VIP игроков (также `vips`, в консоли `mm_vips` и `sm_vips`) |

**vip.phrases.txt**

Допишите внутрь блока `"Phrases"`:

```
"VIPS_Title"
{
	"en"		"VIP players:"
	"ru"		"Вип игроки:"
}
"VIPS_NoPlayers"
{
	"en"		"No VIP players found"
	"ru"		"Не найдено ни одного вип игрока"
}
"VIPS_Player"
{
	"en"		"%s (%s)"
	"ru"		"%s (%s)"
}
"VIPS_Player2"
{
	"en"		"%s"
	"ru"		"%s"
}
```

**Конфиг**

`addons/configs/vip/vip_vips.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `type` | `0` | 1 показывать только ник, 0 ник и VIP группу |

```
"VIP"
{
    "type"     "0"     //Скрыть ли вип группу?(1/0)
}
```

## Сборка

Собирается на Linux. Нужны clang, python3, cmake и [AMBuild](https://github.com/alliedmodders/ambuild). Все команды ниже выполняются из одной папки.

**1. SDK.** Нужен [sourcesdk](https://github.com/Wend4r/sourcesdk) не старее обновления CS2 от 12.11.2026. Собирается один раз:

```bash
git clone --recursive https://github.com/Wend4r/sourcesdk hl2sdk-cs2
cmake -S hl2sdk-cs2 -B hl2sdk-cs2/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DSOURCESDK_AM_DEFINES=ON -DSOURCESDK_USE_MINIMAL_PROTOS=OFF
cmake --build hl2sdk-cs2/build -j$(nproc)
export HL2SDKCS2=$PWD/hl2sdk-cs2
```

**2. Metamod.** Нужен Metamod 2.0 с KHook, ветка `master`. Со старым Metamod на SourceHook сборка остановится с ошибкой.

```bash
git clone --recursive https://github.com/alliedmodders/metamod-source
```

**3. Модуль.** Папка SchemaEntity уже лежит в корне репозитория, модули берут её оттуда.

```bash
git clone https://github.com/Cookies2122/vip-modules
cd vip-modules/VIP_AntiFlash
mkdir build && cd build
python3 ../configure.py --enable-optimize --sdks=cs2 --targets=x86_64 --mms_path=$PWD/../../../metamod-source --hl2sdk-manifests=../hl2sdk-manifests
ambuild
```

Готовые файлы появятся в `build/package`. Для другого модуля поменяйте папку во второй строке, папки с пробелами берите в кавычки, например `cd "vip-modules/[VIP] Weapon Kit"`.

## Авторы

| Модуль | Автор | Оригинал |
| --- | --- | --- |
| [[VIP] Infinite Ammo](%5BVIP%5D%20Infinite%20Ammo) | [\_ded\_cookies](https://github.com/Cookies2122) | этот репозиторий |
| [[VIP] Respawn++](%5BVIP%5D%20Respawn%2B%2B) | [\_ded\_cookies](https://github.com/Cookies2122) и E!N | этот репозиторий |
| [[VIP] Weapon Kit](%5BVIP%5D%20Weapon%20Kit) | [\_ded\_cookies](https://github.com/Cookies2122) | этот репозиторий |
| [[VIP] Reserved slots](%5BVIP%5D%20Reserved%20slots) | [\_ded\_cookies](https://github.com/Cookies2122) | этот репозиторий |
| [[VIP] Regen Ammo](%5BVIP%5D%20Regen%20Ammo) | [\_ded\_cookies](https://github.com/Cookies2122) | этот репозиторий |
| [VIP_AntiFlash](VIP_AntiFlash) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_AntiFlash) |
| [VIP_AwpManager](VIP_AwpManager) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_AwpManager) |
| [VIP_BaseFunctions](VIP_BaseFunctions) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_BaseFunctions) |
| [VIP_Bhop](VIP_Bhop) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Bhop) |
| [VIP_BuyTeamWeapon](VIP_BuyTeamWeapon) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_BuyTeamWeapon) |
| [VIP_DuckSpeed](VIP_DuckSpeed) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_DuckSpeed) |
| [VIP_Endurance](VIP_Endurance) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Endurance) |
| [VIP_FOV](VIP_FOV) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_FOV) |
| [VIP_FastDefuse](VIP_FastDefuse) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_FastDefuse) |
| [VIP_FastPlant](VIP_FastPlant) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_FastPlant) |
| [VIP_Fortnite_Hits](VIP_Fortnite_Hits) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Fortnite_Hits) |
| [VIP_Gravity](VIP_Gravity) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Gravity) |
| [VIP_Healthshot](VIP_Healthshot) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Healthshot) |
| [VIP_Items](VIP_Items) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Items) |
| [VIP_JoinSound](VIP_JoinSound) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_JoinSound) |
| [VIP_Jumps](VIP_Jumps) | [Pisex](https://github.com/Pisex) и [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Jumps) |
| [VIP_KillScreen](VIP_KillScreen) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_KillScreen) |
| [VIP_MultiTest](VIP_MultiTest) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_MultiTest) |
| [VIP_NoFallDamage](VIP_NoFallDamage) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_NoFallDamage) |
| [VIP_Penis](VIP_Penis) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Penis) |
| [VIP_RainbowModel](VIP_RainbowModel) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_RainbowModel) |
| [VIP_RegenArmor](VIP_RegenArmor) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_RegenArmor) |
| [VIP_RegenHP](VIP_RegenHP) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_RegenHP) |
| [VIP_ResetDeaths](VIP_ResetDeaths) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_ResetDeaths) |
| [VIP_Respawn](VIP_Respawn) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Respawn) |
| [VIP_ShowDamage](VIP_ShowDamage) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_ShowDamage) |
| [VIP_Skins](VIP_Skins) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Skins) |
| [VIP_Smoke](VIP_Smoke) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Smoke) |
| [VIP_Speed](VIP_Speed) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Speed) |
| [VIP_Tag](VIP_Tag) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Tag) |
| [VIP_TeammatesHeal](VIP_TeammatesHeal) | [ABKAM](https://github.com/ABKAM2023) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_TeammatesHeal) |
| [VIP_Test](VIP_Test) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Test) |
| [VIP_Time](VIP_Time) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Time) |
| [VIP_Vampirism](VIP_Vampirism) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Vampirism) |
| [VIP_Vips](VIP_Vips) | [Pisex](https://github.com/Pisex) | [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Vips) |

Автор каждого модуля указан и в самом коде, в функции `GetAuthor`. Перенос модулей Pisex и ABKAM на новый SDK и Metamod 2.0 и исправления: \_ded\_cookies.

## Лицензия

Репозиторий распространяется по лицензии GPL-3.0, текст в файле [LICENSE](LICENSE). Авторские права на модули остаются за их авторами из таблицы выше.
