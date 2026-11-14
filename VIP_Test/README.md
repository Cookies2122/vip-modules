# VIP_Test

Тестовый VIP: игрок пишет `!viptest` и получает группу на время.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_Test). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

Не ставьте вместе с VIP_MultiTest: у них одинаковые команды и один файл `vip_test.ini`.

## Команды

| Команда | Что делает |
| --- | --- |
| `!viptest` | получить тестовый VIP |
| `!testvip` | то же самое |
| `mm_viptest` | то же из консоли, также `sm_viptest`, `mm_testvip`, `sm_testvip` |

## vip.phrases.txt

Фразы `AlreadyVIP`, `AlreadyReceived`, `ReceivedDisabled` уже есть в vip.phrases.txt ядра.

## Конфиг

`addons/configs/vip/vip_test.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `group` | `VIP` | какую VIP группу выдавать |
| `time` | `60` | на сколько секунд |
| `timeout` | `0` | через сколько секунд после окончания можно взять снова, 0 только один раз |

```
"VIP"
{
    "group"     "VIP"
    "time"      "60"
    "timeout"   "0"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
