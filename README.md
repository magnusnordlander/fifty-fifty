# fifty-fifty
A grinder controller for my Mazzer Major

## Status
This project is in use and development.

*There will be a Rev B PCB*. The Rev A PCB works, but unless you can print your own PCBs, you probably want to wait for the rev B.

### Upcoming Rev B changes
* Possibly SMD components (except the Arduino, obviously)
* Populate the entire UEXT header, allowing for SPI displays
* Load cell interface - ADS1232
  * Possible 5V regulator: L7805CDT-TR (for increased accuracy, though 3V3 seems very feasible)
  * Possibly use an RC filter to filter REFP, REFN, AINP1 and AINN1

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

* 1 x [DIL socket 32 pin (remove 2 pins, optional but recommended)](https://www.electrokit.com/en/product/dil-socket-32-pin/)
* 1 x [3 mm LED, 2.15 V forward voltage, 20mA](https://www.electrokit.com/en/product/led-red-3-mm-500-mcd-clear/)
* 1 x [100Ω resistor, R1 (or another resistor appropriate for the LED you're using), incorrectly labled as 1K on the PCB](https://www.electrokit.com/en/product/resistor-metal-film-0-6w-1-100ohm-100r/)
* 1 x [1kΩ resistor, R2](https://www.electrokit.com/en/product/resistor-metal-film-0-6w-1-1kohm-1k/)
* 1 x [IRLZ44NPBF TO-220 N-ch 55V 47A MOSFET, incorrectly labeled as IRF520 on the PCB](https://www.electrokit.com/en/product/irlz44npbf-to-220-n-ch-55v-47a-2/)
* 1 x [PCB pin header 5.08mm 6-pole right-angle](https://www.electrokit.com/en/product/pcb-hane-5-08mm-6-pol-vinklad/)
* 1 x [IDC box header PCB 10-p 2.54mm](https://www.electrokit.com/en/product/idc-box-header-pcb-10-p-2-54mm/)
* 1 x [5 pin 2.43mm pin header](https://www.electrokit.com/en/product/pin-header-2-54mm-1x40p-red/)

## Anything else?

While not technically part of the board, you'll probably want some other things to make it all work:

* 1 x [Screw terminal pluggable 5.08mm 6-pole](https://www.electrokit.com/en/product/skruvplint-pluggbar-5-08mm-6-pol/)
* 1 x 10 pin IDC flat cable
* 1 x 5 pin jumper wires
