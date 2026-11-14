# VIP_RegenArmor

Восстанавливает броню VIP игрока после урона.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_RegenArmor). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"RegenArmor"          "10"
"DelayRegenArmor"     "5"
"IntervalRegenArmor"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `RegenArmor` | сколько брони за раз |
| `DelayRegenArmor` | через сколько секунд после урона начать |
| `IntervalRegenArmor` | раз в сколько секунд |

С примером выше через 5 секунд после урона броня растёт на 10 каждые 2 секунды. Максимум 100 или значение `armor` из VIP_BaseFunctions.

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"RegenArmor"
{
	"en"		"Regen Armor"
	"ru"		"Реген Брони"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
