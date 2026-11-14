# VIP_Gravity

Меняет гравитацию VIP игрока.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Gravity). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"gravity"  "0.8"
```

| Ключ | Что значит |
| --- | --- |
| `gravity` | 1.0 обычная, меньше прыжок выше, больше тяжелее, можно от 0.1 до 2.0 |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"gravity"
{
	"en"		"Gravity"
	"ru"		"Гравитация"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
