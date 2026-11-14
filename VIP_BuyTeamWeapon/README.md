# VIP_BuyTeamWeapon

VIP игрок может купить оружие команды противника прямо из чата, например АК за CT.

Автор: [Pisex](https://github.com/Pisex). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_BuyTeamWeapon). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"btw"  "1"
```

| Ключ | Что значит |
| --- | --- |
| `btw` | доступ, 1 да, 0 нет |

Купить можно только в зоне закупки и если хватает денег. В меню VIP этого пункта нет, поэтому фраза `btw` не нужна.

## Команды

| Команда | Что делает |
| --- | --- |
| `!<название>` | купить оружие из конфига, например `!ak47` за CT или `!m4a1` за T. В консоли `mm_<название>` |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"btw_round_start"
{
	"en"		"The purchase of opposing team weapons is available to you: %s"
	"ru"		"Вам доступна покупка оружия команды противника: %s"
}
"btw_no_money"
{
	"en"		"Not enough money to buy a gun"
	"ru"		"Недостаточно денег для покупки оружия"
}
"btw_no_buyzone"
{
	"en"		"You can't buy a gun when you're not in the purchasing area"
	"ru"		"Вы не можете купить оружие, если вы не находитесь в зоне покупки"
}
```

## Конфиг

`addons/configs/vip/vip_btw.ini`

Секция `CT` это то, что может купить CT, секция `T` то, что может купить T. Имя внутри секции это команда (`ak47` даёт `!ak47` и `mm_ak47`), `price` цена, `weapon` что выдать.

<details>
<summary>Весь файл vip_btw.ini</summary>

```
"VIP"
{
    "CT"
    {
        "ak47"  //!ak47 and mm_ak47
        {
            "price"     "2700"
            "weapon"    "weapon_ak47"
        }
    }
    "T"
    {
        "m4a1"  //!m4a1 and mm_m4a1
        {
            "price"     "2900"
            "weapon"    "weapon_m4a1_silencer"
        }
        "m4a4"  //!m4a4 and mm_m4a4
        {
            "price"     "3100"
            "weapon"    "weapon_m4a1"
        }
    }
}
```

</details>

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
