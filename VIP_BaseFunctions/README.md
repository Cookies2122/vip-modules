# VIP_BaseFunctions

При возрождении выдаёт VIP игроку здоровье, броню, шлем, дефьюзер и деньги.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_BaseFunctions). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

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

## vip.phrases.txt

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

## Конфиг

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

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
