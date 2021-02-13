//
// Created by Magnus Nordlander on 2021-02-13.
//

#include <avr/dtostrf.h>
#include "ScaleViewController.h"

ScaleViewController::ScaleViewController(ScaleWrapper *scale) : scale(scale) {
}

void ScaleViewController::render(U8G2 display) {
    if (this->taring) {
        display.setFont(u8g2_font_helvB12_te);
        display.drawStr(36,56, "Taring");
    } else {
        char time_string[25];
        dtostrf(this->scale->getLatestValue(), 3, 1, time_string);

        display.setFont(u8g2_font_helvB12_te);
        display.drawStr(36,56, time_string);
    }
}

void ScaleViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->navigationController->pop();
    } else if (event == BUTTON_LET_UP) {
        this->taring = true;
        this->scale->tareNoDelay();
    }
}

void ScaleViewController::tick(U8G2 display) {
    if (this->scale->getTareStatus()) {
        this->taring = false;
    }

    BaseViewController::tick(display);
}
