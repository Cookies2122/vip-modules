# VIP_AwpManager

Меняет число патронов в магазине AWP у VIP игрока.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_AwpManager). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"awp_manager"  "10"
```

| Ключ | Что значит |
| --- | --- |
| `awp_manager` | сколько патронов в магазине |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"awp_manager"
{
	"en"		"AWP Manager"
	"ru"		"AWP Manager"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
