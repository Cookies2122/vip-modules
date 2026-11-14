# VIP_DuckSpeed

Быстрое приседание для VIP игрока.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_DuckSpeed). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"duckspeed"  "10.0"
```

| Ключ | Что значит |
| --- | --- |
| `duckspeed` | скорость приседания, чем больше, тем быстрее |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"duckspeed"
{
	"en"		"Fast Crouch"
	"ru"		"Быстрое приседание"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
