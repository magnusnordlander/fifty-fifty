//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "ManualGrindViewController.h"

void ManualGrindViewController::render(U8G2 display) {
    display.clearBuffer();
    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(36,56, "Manual");

    unsigned long elapsed_ms = this->elapsedMillis();

    char time_string[25];
    snprintf(time_string, sizeof(time_string), "%d.%02d", (int)elapsed_ms/1000, (int)(elapsed_ms/10)%100);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
    if (elapsed_ms < 10000) {
        display.drawStr(24,32,time_string);
        display.drawStr(96, 32, "s");
    } else {
        display.drawStr(8,32,time_string);
        display.drawStr(100, 32, "s");
    }

    display.sendBuffer();
}
