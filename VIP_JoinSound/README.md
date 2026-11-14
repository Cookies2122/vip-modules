# VIP_JoinSound

Когда VIP заходит на сервер, всем игрокам играет звук.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [Pisex/cs2-vip-modules](https://github.com/Pisex/cs2-vip-modules/tree/main/VIP_JoinSound). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [VIP Core](https://github.com/Pisex/cs2-vip)
- [Utils](https://github.com/Pisex/cs2-menus)

## groups.ini

```
"JoinSound"  "sounds/music/vip_join.vsnd_c"
```

| Ключ | Что значит |
| --- | --- |
| `JoinSound` | путь к звуку |

Звук запускается у игроков командой `play`, поэтому файл должен быть у них: в самой игре или в аддоне сервера.

## vip.phrases.txt

Допишите внутрь блока `"Phrases"`:

```
"JoinSound"
{
	"en"		"Join Sound"
	"ru"		"Звук при подключении"
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
