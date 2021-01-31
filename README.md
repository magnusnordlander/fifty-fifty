# fifty-fifty
A grinder controller for my Mazzer Major

## Status
This project is in use and development.

*There will be a Rev B PCB*. The Rev A PCB works, but unless you can print your own PCBs, you probably want to wait for the rev B.

### Upcoming Rev B changes
* SMD components (except the Arduino, obviously)
* Populate the entire UEXT header, allowing for SPI displays
* Load cell interface

## Overview

This is an Arduino based grinder controller for my Mazzer Major. It has a display and is controlled by a rotary encoder. It also contains a PCB schematic.

## Parts

* [Arduino Nano 33 IoT](https://www.electrokit.com/en/product/arduino-nano-33-iot-with-headers/)
* A Solid-state relay
  * I'm using a [Fotek SSR-40 DA clone](https://www.electrokit.com/en/product/solid-state-relay-3-32v-40a/), because that's what came with my used grinder when I bought it
  * If you want a more high-quality component, a [Crydom-Sensata 84137000](http://www.crydom.com/en/products/catalog/gnssr.pdf) would be a good choice
* A power supply in the range of 3.3-20 V capable of driving both the Arduino and the SSR
  * I'm using a no-name 9V power supply that came with my used grinder
  * A good choice for buying would be something like the [Mean-Well IRM-20-12](https://www.electrokit.com/en/product/switchad-stromforsorjning-20w-12v-2/)
* A [KY-040 style rotary encoder](https://www.electrokit.com/en/product/rotary-encoder-module/)
* An [SSD1306 compatible, I2C connected, 3.3V, 128x64 px OLED, preferably (but not necessarily) connected via UEXT](https://www.electrokit.com/en/product/lcd-oled-0-96-128-x-64px-uext-2/)


## Rev A BOM

TBD
