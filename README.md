# fifty-fifty
A grinder controller for my Mazzer Major

## Status
This project is in use and development. Current PCB Revision is Rev C.

*There will be a Rev D PCB*. The Rev D PCB will adjust the fit for a Futurekit FB20 box (it's currently slightly too large, and the mounting holes are misaligned). 

### Changelog

* Rev A: First revision board
* Rev B: Substantial changes. ADS1232 load cell interface, SMT components, fully populated UEXT connector (was printed).
  * Errata: Resistor R2 never should have existed. Remove R2 or cut trace from R2 to GND.
  * Errata: R3 and R4 silk screens are flipped around. They're the same value though, so it doesn't make any material difference.
* Rev C: Removed the resistor that was R2 in Rev B (hasn't been printed), fixed silk screen, added dots for SMT ICs.
  * Errata: Doesn't quite fit in the intended Futurekit FB20 box.

## Overview

This is an Arduino based grinder controller for my Mazzer Major. It has a display and is controlled by a rotary encoder. It also contains a PCB schematic.

## Features

* Grinder control via a simple to use interface, controlled by a rotary encoder
* Timed grinding
* Grind by weight
  * An ADS1232 load cell interface, sampling a load cell at 80 SPS.
  * High accuracy
  * Fast taring

## Parts

* [Arduino Nano 33 IoT](https://www.electrokit.com/en/product/arduino-nano-33-iot-with-headers/)
* A Solid-state relay
  * I'm using a [Fotek SSR-40 DA clone](https://www.electrokit.com/en/product/solid-state-relay-3-32v-40a/), because that's what came with my used grinder when I bought it
  * If you want a more high-quality component, a [Crydom-Sensata 84137000](http://www.crydom.com/en/products/catalog/gnssr.pdf) would be a good choice
* A high quality 5.3-6.0V power supply. I'm using a [Mean Well RS-15-5](https://www.amazon.se/gp/product/B00MWQD43U/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&psc=1). Quality matters for minimizing ADC interference. A 5V power supply with an adjustment potentiometer should do fine, the LDO will regulate anything between 5.3 and 6.0 V to 5V for the ADC. Set your PSU to 5.5V and all will be good.
* A [KY-040 style rotary encoder](https://www.electrokit.com/en/product/rotary-encoder-module/)
* An [SSD1309, SPI connected, 3.3V, 128x64 px OLED](https://www.electrokit.com/produkt/lcd-oled-2-42-12x64px-spi-i2c/)
* A [1000 g whetstone bridge load cell](https://www.electrokit.com/produkt/lastcell-1kg/)


## THT BOM

* 1 x [DIL socket 32 pin (remove 2 pins, optional but recommended)](https://www.electrokit.com/en/product/dil-socket-32-pin/) (For the Arduino)
* 1 x [PCB pin header 5.08mm 6-pole right-angle](https://www.electrokit.com/en/product/pcb-hane-5-08mm-6-pol-vinklad/) (For power, SSR and manual grind knob connection)
* 1 x [IDC box header PCB 10-p 2.54mm](https://www.electrokit.com/en/product/idc-box-header-pcb-10-p-2-54mm/) (For display connection)
* 1 x [Screw terminal 2.54mm 4-pole](https://www.electrokit.com/produkt/skruvplint-2-54mm-4-pol/) (For load cell connection)
* 1 x [5 pin 2.54mm pin header](https://www.electrokit.com/en/product/pin-header-2-54mm-1x40p-red/) (For rotary encoder connection)
* 1 x 3 pin 2.54mm pin header (For ADC debug voltage jumper)
* 1 x [2.54mm jumper](https://www.electrokit.com/produkt/bygel-2-54mm-2p-svart/)

## Anything else?

While not technically part of the board, you'll probably want some other things to make it all work:

* 1 x [Screw terminal pluggable 5.08mm 6-pole](https://www.electrokit.com/en/product/skruvplint-pluggbar-5-08mm-6-pol/)
* 1 x 10 pin IDC flat cable
* 1 x 5 pin jumper wires
* Wiring
  * 0.75 mm² (or higher) copper wiring for the high voltage side
    * Preferably in standard colors, which would be blue/brown in Europe for neutral/load. Signal wire from SSR to the motor can be any other color except green/yellow. Orange is a good choice.
  * Wiring cable, I'd go for 0.20 mm² copper. Preferably in red and black.
* WAGO 221 splicing connectors
* A 100.0 g reference weight for scale calibration
