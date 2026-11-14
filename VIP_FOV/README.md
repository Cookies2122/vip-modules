# VIP_FOV

VIP игрок выбирает себе угол обзора (FOV) в меню.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_FOV). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"FOV"  "100,90,80,70,60"
```

| Ключ | Что значит |
| --- | --- |
| `FOV` | варианты FOV через запятую, они будут в меню |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"FOV"
{
	"en"		"Viewing angle"
	"ru"		"Угол обзора"
}
"FOV_Title"
{
	"en"		"Select FOV"
	"ru"		"Выберите FOV"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
