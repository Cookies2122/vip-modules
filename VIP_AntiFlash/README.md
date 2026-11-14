# VIP_AntiFlash

VIP игрока не слепят флешки. Можно выбрать, какие именно.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_AntiFlash). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"antiflash"  "3"
```

| Ключ | Что значит |
| --- | --- |
| `antiflash` | режим, смотрите таблицу ниже |

| Значение | Что будет |
| --- | --- |
| `1` | не слепят флешки тиммейтов |
| `2` | не слепят свои флешки |
| `3` | не слепят свои флешки и флешки тиммейтов |
| `4` | не слепят никакие флешки |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"antiflash"
{
	"en"		"Anti-Flash"
	"ru"		"Антифлеш"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
