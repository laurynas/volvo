## Controlling Volvo V50 '07 RTI screen with Arduino

[Video of the project](https://www.youtube.com/watch?v=QqmE6McCTZU).

I used Arduino 12V power adapter to power the screen.

### Display

VGA signal is generated from Arduino UNO using customized [VGAX library](arduino/VGAXS/). I have changed VGAX HSYNC interval to 64μs, adjusted positioning, pixel timing. 

Display uses VGA Composite Sync signal, so HSYNC & VSYNC signals must be combined into one. I tried just connecting both wires to video sync pin and it worked! So, no need for [signal combining logic](http://www.epanorama.net/circuits/vga2rgbs.html).

Arduino UNO [VGA example](arduino/vga_pirate.ino). In this example I have used native `Serial` and inverted serial signal with extra transistor.

[<img width='50%' src='docs/pirate.jpg'/>](docs/pirate.jpg)

### Schemes

- [Power connection](https://raw.githubusercontent.com/laurynas/volvo/master/doc/power_connection.png)
- [Screen connection](https://raw.githubusercontent.com/laurynas/volvo/master/doc/screen_connection.png). I used `2SC945` transistor, a bit different from the one in the scheme. It worked fine.

### Thanks!

While digging for information I found the most useful info here:

- Reinis Veps [CarPC project](http://wot.lv/category/rpi-carpc.html)
- Niclas Lardh [discussion](http://www.svxc.se/phpBB2/viewtopic.php?t=22034)
- maniacus [CarPC project](https://www.drive2.ru/l/6048661/)
- Nick Gammon & Sandro Maffiodo [VGAX library for Arduino UNO](https://github.com/smaffer/vgax)