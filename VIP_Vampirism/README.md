# VIP_Vampirism

VIP игрок получает здоровье за урон по врагу.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Vampirism). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"Vampirism"  "10"
```

| Ключ | Что значит |
| --- | --- |
| `Vampirism` | сколько процентов от урона вернётся здоровьем |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"Vampirism"
{
	"en"		"Vampirism"
	"ru"		"Вампиризм"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
