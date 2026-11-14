# VIP_MultiTest

Тестовый VIP с выбором группы. Игрок пишет `!testvip` и в меню выбирает, какую группу попробовать.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_MultiTest). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

Не ставьте вместе с VIP_Test: у них одинаковые команды и один файл `vip_test.ini`.

## Команды

| Команда | Что делает |
| --- | --- |
| `!testvip` | открыть меню тестового VIP |
| `!viptest` | то же самое |
| `mm_testvip` | то же из консоли, также `sm_testvip`, `mm_viptest`, `sm_viptest` |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"VIPTest_Title"
{
	"en"		"Choose a VIP group"
	"ru"		"Выберите вип группу"
}
```

Фразы `AlreadyVIP`, `AlreadyReceived`, `ReceivedDisabled` уже есть в vip.phrases.txt ядра.

## Конфиг

`addons/configs/vip/vip_test.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `type` | `1` | 1 общий timeout: взял одну группу, другие нельзя, пока не пройдёт timeout. 2 у каждой группы свой timeout |

Остальные секции это группы. Имя секции это имя VIP группы, `display` название в меню, `time` на сколько секунд выдаётся, `timeout` через сколько секунд после окончания можно взять снова (0 только один раз).

```
"VIP"
{
    "type"      "1"     //Тип получения випки
                        //1 - Глобальный timeout, пример: игрок взял Example1 и не может взять Example2 пока не пройдет timeout
                        //2 - Timeout по группе, пример: игрок взял Example1 и после этого может взять Example2

    "Example1"    //Вип группа
    {
        "display"   "Lite-VIP"  //Отображаемое имени в меню
        "time"      "7200"      //Время выдачи випки в секундах
        "timeout"   "14400"     //Перезарядка между повторными получениями випки в секундах(0 - никогда)
    }
    "Example2"    //Вип группа
    {
        "display"   "VIP"       //Отображаемое имени в меню
        "time"      "3600"      //Время выдачи випки в секундах
        "timeout"   "14400"     //Перезарядка между повторными получениями випки в секундах(0 - никогда)
    }
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
