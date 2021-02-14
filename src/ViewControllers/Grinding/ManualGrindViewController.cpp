//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "ManualGrindViewController.h"
#include <Utils/TextUtils.h>

void ManualGrindViewController::render(U8G2 display) {

    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(36,56, "Manual");

    unsigned long elapsed_ms = this->elapsedMillis();

    drawLargeFloatWithUnits(display, (float)elapsed_ms/1000., "s", 32, 3, 2);
}
