//
// Created by Magnus Nordlander on 2021-02-13.
//

#include <avr/dtostrf.h>
#include "ScaleViewController.h"

ScaleViewController::ScaleViewController(ScaleWrapper *scale) : scale(scale) {
    this->progressBar = new ProgressBarView;
}

void ScaleViewController::render(U8G2 display) {
    if (this->taring) {
        display.setFont(u8g2_font_helvB12_te);
        display.drawStr(32,36, "Taring...");

        this->progressBar->drawRelative(display, 14, 54);
    } else {
        char time_string[25];
        dtostrf(this->scale->getLatestValue(), 3, 1, time_string);

        char full[25];

        snprintf(full, sizeof(full), "%s g", time_string);

        display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font

        unsigned short x;
        switch (strlen(full)) {
            case 5:
                x = 24;
                break;
            case 6:
                x = 16;
                break;
            case 7:
                x = 8;
                break;
            default:
                x = 0;
                break;
        }

        display.drawStr(x,42,full);
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

ScaleViewController::~ScaleViewController() {
    delete this->progressBar;
}
