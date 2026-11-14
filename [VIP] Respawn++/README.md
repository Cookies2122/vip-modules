# [VIP] Respawn++

Расширенный респавн: возрождение по команде и автореспавн после смерти. Есть лимиты по времени раунда, по числу игроков и по числу живых.

Автор: [\_ded\_cookies](https://github.com/Cookies2122) и E!N.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"respawn"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `respawn` | доступ к респавну, 1 включено, 0 нет |

Не ставьте вместе с VIP_Respawn: у них один ключ `respawn` и одинаковое имя файла `vip_respawn.so`.

## Команды

| Команда | Что делает |
| --- | --- |
| `!respawn` | возродиться (также `respawn`, в консоли `mm_respawn` и `sm_respawn`) |

## vip.phrases.txt

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

## Конфиг

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

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
