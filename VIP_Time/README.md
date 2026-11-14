# VIP_Time

В заданное время выдаёт VIP группу всем игрокам, например ночью.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Time). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

Время проверяется раз в минуту. Группа выдаётся только тем, у кого VIP нет, в базу не сохраняется и снимается, когда время закончилось.

## Конфиг

`addons/configs/vip/vip_time.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `group` | `VIP` | какую VIP группу выдавать |
| `start_time` | `22:00` | с какого времени, часы:минуты |
| `end_time` | `08:00` | до какого времени, можно через полночь |

```
"VIP"
{
	"group"		"VIP"
	"start_time"	"22:00"
	"end_time"	"08:00"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
