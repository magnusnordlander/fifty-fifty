//
// Created by Magnus Nordlander on 2021-02-13.
//

#include "CalibrationViewController.h"

void CalibrationViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

    switch (this->state) {
        case STATE_PRE_TARE:
            display.drawStr(8,42,"Press button to tare");
            break;
        case STATE_TARING:
            display.drawStr(8,42,"Taring");
            break;
        case STATE_TARED:
            display.drawStr(8,42,"Place 100g on scale and press button");
            break;
        case STATE_MEASURING:
            display.drawStr(8,42,"Calibrating");
            break;
    }

}

CalibrationViewController::CalibrationViewController(Settings *settings, ScaleWrapper *scale) {
    this->settings = settings;
    this->scale = scale;
}

void CalibrationViewController::viewWillBePushed(NavigationController *controller) {
    BaseViewController::viewWillBePushed(controller);

    this->state = STATE_PRE_TARE;
    this->scale->setAccurateMode(true);
}

void CalibrationViewController::viewWasPopped(NavigationController *controller) {
    BaseViewController::viewWasPopped(controller);

    this->state = STATE_PRE_TARE;
    this->scale->setAccurateMode(false);
}

void CalibrationViewController::tick(U8G2 display) {
    BaseViewController::tick(display);

    if (this->state == STATE_TARING && this->scale->getTareStatus()) {
        this->state = STATE_TARED;
    }

    if (this->state == STATE_MEASURING && this->scale->accuracyBufferFull()) {
        this->settings->setScaleCalibration(this->scale->measureCalibrationValue(100.));
        this->navigationController->pop();
    }
}

void CalibrationViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        if (this->state == STATE_PRE_TARE) {
            this->state = STATE_TARING;
            this->scale->tareNoDelay();
        } else if (this->state == STATE_TARED) {
            this->state = STATE_MEASURING;
            this->scale->clearAccuracyBuffer();
        }
    }
}
