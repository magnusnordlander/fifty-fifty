//
// Created by Magnus Nordlander on 2021-02-13.
//

#include <avr/dtostrf.h>
#include "ScaleViewController.h"

ScaleViewController::ScaleViewController(ScaleWrapper *scale) : scale(scale) {
}

void ScaleViewController::render(U8G2 display) {
    char time_string[25];
    dtostrf(this->scale->getLatestValue(), 3, 1, time_string);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(36,56, time_string);
}

void ScaleViewController::handleButtonState(bool state) {
    if (state) {
        this->navigationController->pop();
        delay(200);
    }
}
