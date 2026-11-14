# VIP_Vips

Команда `!vips` показывает список VIP игроков на сервере.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Vips). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## Команды

| Команда | Что делает |
| --- | --- |
| `!vips` | список VIP игроков (также `vips`, в консоли `mm_vips` и `sm_vips`) |

## vip.phrases.txt

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

## Конфиг

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

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
