# VIP_Speed

Меняет скорость бега VIP игрока.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Speed). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"speed"  "1.1"
```

| Ключ | Что значит |
| --- | --- |
| `speed` | 1.0 обычная, 1.1 немного быстрее, можно от 0.1 до 2.0 |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"speed"
{
	"en"		"Speed"
	"ru"		"Скорость"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
