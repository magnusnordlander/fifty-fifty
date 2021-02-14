//
// Created by Magnus Nordlander on 2021-02-13.
//

#include <Utils/TextUtils.h>
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
        drawLargeFloatWithUnits(display, this->scale->getLatestValue(), "g", 42);
    }
}

void ScaleViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->taring = true;
        this->scale->tareNoDelay();
    } else if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
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
