# VIP_RegenHP

Восстанавливает здоровье VIP игрока после урона.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_RegenHP). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"RegenHP"          "10"
"DelayRegenHP"     "5"
"IntervalRegenHP"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `RegenHP` | сколько HP за раз |
| `DelayRegenHP` | через сколько секунд после урона начать |
| `IntervalRegenHP` | раз в сколько секунд |

С примером выше через 5 секунд после урона здоровье растёт на 10 каждые 2 секунды, до максимального здоровья игрока.

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"RegenHP"
{
	"en"		"Regen HP"
	"ru"		"Реген ХП"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
