# VIP_Penis

Шуточный модуль: вешает модель на VIP игрока.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Penis). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"penis"        "1"
"penis_model"  "models/kolka/penis/penis.vmdl"
```

| Ключ | Что значит |
| --- | --- |
| `penis` | 1 включено, 0 нет |
| `penis_model` | путь к модели |

Модель должна быть в аддоне сервера и в прекеше, например через [ResourcePrecacher](https://github.com/Pisex/ResourcePrecacher). Модели из оригинала: `models/kolka/penis/penis_weapon.vmdl`, `penis_small.vmdl`, `penis_medium.vmdl`, `penis.vmdl`.

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"penis"
{
	"en"		"Penis"
	"ru"		"Пенис"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
