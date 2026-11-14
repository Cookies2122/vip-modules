# VIP_FastDefuse

VIP игрок быстрее разминирует бомбу.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_FastDefuse). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"fd"  "50"
```

| Ключ | Что значит |
| --- | --- |
| `fd` | на сколько процентов быстрее |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"fd"
{
	"en"		"Fast Defuse"
	"ru"		"Быстрое обезвреживание"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
