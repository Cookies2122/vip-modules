# VIP_Respawn

VIP игрок может возродиться командой `!respawn`.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Respawn). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"respawn"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `respawn` | сколько раз за раунд |

Не ставьте вместе с [VIP] Respawn++: у них один ключ `respawn` и одинаковое имя файла `vip_respawn.so`.

## Команды

| Команда | Что делает |
| --- | --- |
| `!respawn` | возродиться (также `respawn`, в консоли `mm_respawn` и `sm_respawn`) |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"respawn"
{
	"en"		"Respawn"
	"ru"		"Респавн"
}
```

Фразы `EndRound`, `LimitRespawn`, `SelectTeam`, `YourAlive` уже есть в vip.phrases.txt ядра.

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
