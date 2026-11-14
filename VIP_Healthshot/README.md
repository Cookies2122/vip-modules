# VIP_Healthshot

Каждый раунд выдаёт VIP игроку шприцы.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Healthshot). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"healthshot"  "2"
```

| Ключ | Что значит |
| --- | --- |
| `healthshot` | сколько шприцев |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"healthshot"
{
	"en"		"Healthshots"
	"ru"		"Шприцы"
}
```

## Конфиг

`addons/configs/vip/vip_healthshot.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `round_min` | `2` | с какого раунда выдавать шприцы |

```
"VIP"
{
    "round_min"     "2"     //Только со второго будут выданы шприцы
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
