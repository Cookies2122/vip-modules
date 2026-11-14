# VIP_Fortnite_Hits

Даёт VIP игроку цифры урона в стиле Fortnite из плагина Fortnite Hits.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Fortnite_Hits). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)
- [Fortnite Hits](https://github.com/Pisex/cs2-fortnite_hits)

## groups.ini

```
"fortnite_hits"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `fortnite_hits` | 1 включено, 0 нет |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"fortnite_hits"
{
	"en"		"Damage Display"
	"ru"		"Отображение урона"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
