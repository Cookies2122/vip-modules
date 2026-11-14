# VIP_RainbowModel

Модель VIP игрока переливается цветами.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_RainbowModel). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"rainbow_model"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `rainbow_model` | 1 включено, 0 нет |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"rainbow_model"
{
	"en"		"Rainbow model"
	"ru"		"Разноцветная модель"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
