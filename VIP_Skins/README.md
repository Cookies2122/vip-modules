# VIP_Skins

VIP игрок выбирает себе модель персонажа в меню.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Skins). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"Skins"  "1,2"
```

| Ключ | Что значит |
| --- | --- |
| `Skins` | id скинов из vip_skins.ini через запятую или пробел |

Модели должны быть на сервере и в прекеше, например через [ResourcePrecacher](https://github.com/Pisex/ResourcePrecacher).

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"Skins"
{
	"en"		"Skins"
	"ru"		"Скины"
}
"Disable_Skin"
{
	"en"		"Disable skin"
	"ru"		"Отключить скин"
}
"Select_Skin"
{
	"en"		"Select skin"
	"ru"		"Выберите скин"
}
"Cooldown"
{
	"en"		"The choice will become available in %i seconds"
	"ru"		"Выбор станет доступным через %i сек"
}
```

## Конфиг

`addons/configs/vip/vip_skins.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `time` | `2` | через сколько секунд после возрождения ставить модель |
| `cooldown` | `30` | сколько секунд ждать между сменами скина |

Остальные секции это скины. Имя секции это id, `name` название в меню, `model_ct` модель за CT, `model_t` модель за T.

```
"Skins"
{
	"time"		"2"
	"cooldown"	"30"

	"1"
	{
		"name"		"SAS / Phoenix"
		"model_ct"	"characters/models/ctm_sas/ctm_sas.vmdl"
		"model_t"	"characters/models/tm_phoenix/tm_phoenix.vmdl"
	}
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
