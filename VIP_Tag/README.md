# VIP_Tag

Клан-тег VIP игрока в таблице счёта (TAB).

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Tag). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"clantag"  "[VIP]"
```

| Ключ | Что значит |
| --- | --- |
| `clantag` | текст тега |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"clantag"
{
	"en"		"Clan Tag"
	"ru"		"Клан-Тег"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
