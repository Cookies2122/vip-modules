# [VIP] Reserved slots

Резервные слоты для VIP. Когда обычные слоты заняты, обычный игрок не зайдёт, а VIP зайдёт. Если нужно, плагин освобождает место для VIP.

Автор: [\_ded\_cookies](https://github.com/Cookies2122).

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## Конфиг

`addons/configs/vip/vip_reserved_slots.ini` (при сборке в пакет не попадает, скопируйте файл `configs/vip/vip_reserved_slots.ini` туда сами)

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `public_slots` | `6` | сколько игроков без VIP может быть на сервере одновременно |
| `reserve_slots` | `0` | сколько слотов держать под VIP, если не задан public_slots |
| `vip_groups` | пусто | какие VIP группы пускать в резерв, через `;`, пусто для всех |
| `evict_nonvip` | `0` | 1 кикать одного игрока без VIP, когда VIP заходит на полный сервер, 0 никого не трогать |
| `kick_random` | `0` | кого кикать: 0 первого по слоту, 1 случайного |
| `kick_reason_id` | `135` | причина отключения, 135 это "сервер заполнен" |

Задайте что-то одно: `public_slots` или `reserve_slots`, второе посчитается от maxplayers сервера. Если заданы оба, берётся `public_slots`. Если оба 0, под VIP уходит 2 слота.

<details>
<summary>Весь файл vip_reserved_slots.ini</summary>

```
"ReservedSlots"
{
	// =====================================================================
	//  Можно задать ОДНО из двух полей второе считается автоматически из maxplayers сервера
	//
	//   public_slots    лимит на одновременное число НЕ-VIP игроков
	//   reserve_slots   сколько слотов держать под VIP (maxplayers - public)
	//   maxplayers      указывается в параметрах запуска самого сервера на сайте плагин сам подменит на нужный слот например 10/6 на сервере
	//
	//  Примеры
	//
	//   maxplayers=10, public_slots=6    6 общих + 4 под VIP
	//   maxplayers=20, reserve_slots=4   16 общих + 4 под VIP
	//   maxplayers=12, оба=0             авто (maxplayers - 2) 10 общих + 2 VIP
	//
	//  Если оба заданы берётся public_slots, reserve_slots игнорируется
	// =====================================================================
	"public_slots"     "6"
	"reserve_slots"    "0"

	"vip_groups"       "" 		// Список VIP-групп через ';' можно пусто для всех
	"evict_nonvip"     "0" 		// 1 - когда VIP заходит на ПОЛНОСТЬЮ занятый сервер плагин кикнет одного не VIP, 0 - никого не выгоняем

	"kick_random"      "0" 		// 0 - кикать первого по slot, 1 - случайного
	"kick_reason_id"   "135" 	// ID причины дисконнекта (сервер заполнен)
}
```

</details>

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
