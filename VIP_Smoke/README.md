# VIP_Smoke

Цветной дым у дымовых гранат VIP игрока.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Smoke). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"smoke_color"  "random"
```

| Ключ | Что значит |
| --- | --- |
| `smoke_color` | `random` случайный цвет, или цвет RGB через пробел, например `255 0 0` |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"smoke_color"
{
	"en"		"Colored smoke"
	"ru"		"Цветной смок"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
