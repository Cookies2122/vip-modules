# VIP_ResetDeaths

VIP игрок может обнулить себе смерти или убийства.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_ResetDeaths). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"ResetDeaths"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `ResetDeaths` | 1 доступ есть, 0 нет |

## Команды

| Команда | Что делает |
| --- | --- |
| `!rd` | обнулить смерти (также `rd`, `mm_rd`, `sm_rd`) |
| `!rs` | обнулить убийства (также `rs`, `mm_rs`, `sm_rs`) |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"ResetDeaths"
{
	"en"		"Reset deaths"
	"ru"		"Сброс смертей"
}
"deaths_reset"
{
	"en"		"Your deaths have been reset!"
	"ru"		"Ваши смерти были сброшены!"
}
"deaths_already_zero"
{
	"en"		"Your deaths are already zero."
	"ru"		"Ваши смерти уже равны нулю."
}
"kills_already_zero"
{
	"en"		"Your kills are already zero."
	"ru"		"Ваши убийства уже равны нулю."
}
"kills_reset"
{
	"en"		"Your kills have been reset!"
	"ru"		"Ваши убийства были сброшены!"
}
```

Фразы `NotAccess` уже есть в vip.phrases.txt ядра.

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
