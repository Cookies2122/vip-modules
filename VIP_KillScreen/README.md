# VIP_KillScreen

При убийстве у VIP игрока на экране мелькает цветной эффект.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_KillScreen). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"killscreen"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `killscreen` | 1 включено, 0 нет |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"killscreen"
{
	"en"		"Kill Screen"
	"ru"		"Цветной экран убийства"
}
```

## Конфиг

`addons/configs/vip/vip_ks.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `effect_time` | `0.7` | сколько секунд держится эффект |

```
"VIP"
{
    "effect_time"       "0.7"	//Время отображения эффекта(число с плавающей точкой)
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
