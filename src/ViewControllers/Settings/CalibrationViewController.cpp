//
// Created by Magnus Nordlander on 2021-02-13.
//

#include "CalibrationViewController.h"

void CalibrationViewController::render(U8G2 display) {
    switch (this->state) {
        case STATE_PRE_TARE:
            return this->renderPreTareView(display);
        case STATE_TARING:
            return this->renderTaringView(display);
        case STATE_TARED:
            return this->renderTaredView(display);
        case STATE_MEASURING:
            return this->renderMeasuringView(display);
    }
}

CalibrationViewController::CalibrationViewController(Settings *settings, ScaleWrapper *scale) {
    this->settings = settings;
    this->scale = scale;
    this->progressBar = new ProgressBarView;
}

void CalibrationViewController::viewWillBePushed(NavigationController *controller) {
    BaseViewController::viewWillBePushed(controller);

    this->state = STATE_PRE_TARE;
}

void CalibrationViewController::viewWasPopped(NavigationController *controller) {
    BaseViewController::viewWasPopped(controller);

    this->state = STATE_PRE_TARE;
}

void CalibrationViewController::tick(U8G2 display) {
    BaseViewController::tick(display);

    if (this->state == STATE_TARING && this->scale->isValueStableHighAccuracy()) {
        this->scale->tare(2000000);
        this->state = STATE_TARED;
    }

    if (this->state == STATE_MEASURING && this->scale->isValueStableHighAccuracy()) {
        this->settings->setScaleCalibration(this->scale->measureCalibrationValue(100., 2000000));
        this->navigationController->pop();
    }
}

void CalibrationViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        if (this->state == STATE_PRE_TARE) {
            this->state = STATE_TARING;
        } else if (this->state == STATE_TARED) {
            this->state = STATE_MEASURING;
        }
    }
}

CalibrationViewController::~CalibrationViewController() {
    delete this->progressBar;
}

void CalibrationViewController::renderPreTareView(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    display.drawStr(8,32,"Press button to tare");
}

void CalibrationViewController::renderTaringView(U8G2 display) {
    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,36, "Taring...");

    this->progressBar->drawRelative(display, 16, 54);
}

void CalibrationViewController::renderTaredView(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    display.drawStr(8,20,"Place 100g reference");
    display.drawStr(8, 30, "weight on the scale");
    display.drawStr(8, 40, "and press the button.");
}

void CalibrationViewController::renderMeasuringView(U8G2 display) {
    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(16,36, "Calibrating...");

    this->progressBar->drawRelative(display, 14, 54);
}
