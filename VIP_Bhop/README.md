# VIP_Bhop

Распрыжка (bhop) для VIP игрока.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Bhop). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"bhop"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `bhop` | 1 включено, 0 нет |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"bhop"
{
	"en"		"Bhop"
	"ru"		"Бхоп"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
