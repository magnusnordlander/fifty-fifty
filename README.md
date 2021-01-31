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

## Parts (overview)

* Arduino Nano 33 IoT
* An SSR for controlling the grinder (not mounted on the PCB, it's strictly low voltage)
* A power supply in the range of 3.3-20 V capable of driving both the Arduino and the SSR
* A rotary encoder (I used https://www.m.nu/knappar/rotary-encoder-20p-v-with-switch-breakout-board and the pinout on PCB matches this)
* An I2C controlled OLED (I used https://www.olimex.com/Products/Modules/LCD/MOD-OLED-128x64/open-source-hardware, and the pinout on the PCB matches this)


## Rev A BOM

TBD
