# VIP_TeammatesHeal

VIP игрок лечит союзников, когда стреляет в них.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_TeammatesHeal). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"heal_teammates"  "50"
```

| Ключ | Что значит |
| --- | --- |
| `heal_teammates` | сколько процентов от урона вернётся союзнику здоровьем |

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"heal_teammates"
{
	"en"		"Heal Teammates"
	"ru"		"Лечение союзников"
}
```

## Конфиг

`addons/configs/vip/teammates_heal.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `syringe_effect` | `1` | эффект шприца, 1 включить, 0 выключить |
| `effect_time` | `1.2` | сколько секунд длится эффект |
| `weapon_blacklist` | `weapon_molotov;weapon_hegrenade;` | оружие, которым лечить нельзя, через `;` |
| `max_shot_hp` | `50` | максимум HP за один выстрел |

```
"VIP_Teammates_Heal"
{
    "syringe_effect"     "1"     // Эффект шприца 0 - Выключить, 1 - Включить
    "effect_time"        "1.2"   // Длительность эффекта шприца
    "weapon_blacklist"   "weapon_molotov;weapon_hegrenade;" // Список запрещенного оружия
    "max_shot_hp"        "50"    // Максимальное количество хп, которое можно восстановить за выстрел
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
