# VIP_Items

В начале раунда выдаёт VIP игроку оружие и предметы.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Items). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"items"  "weapon_ak47 weapon_flashbang"
```

| Ключ | Что значит |
| --- | --- |
| `items` | что выдать, через пробел |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"items"
{
	"en"		"Weapons at the start of a round"
	"ru"		"Оружие в начале раунда"
}
```

## Конфиг

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

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
