# VIP_NoFallDamage

VIP игрок не получает урон от падения.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_NoFallDamage). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"nofalldamage"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `nofalldamage` | 1 включено, 0 нет |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"nofalldamage"
{
	"en"		"No Fall Damage"
	"ru"		"Отключение урона от падения"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
