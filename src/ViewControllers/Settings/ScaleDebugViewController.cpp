//
// Created by Magnus Nordlander on 2021-02-21.

#include <avr/dtostrf.h>
#include "ScaleDebugViewController.h"

void ScaleDebugViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr);

    char full[32];
    char num[10];

    dtostrf(this->scale->scaleStandardDeviation(2000000, 15), 2, 0, num);
    snprintf(full, sizeof(full), "SD: %s", num);
    display.drawStr(0,8, full);

    microtime_t bufTimeMillis = this->scale->bufSize()/1000;
    snprintf(full, sizeof(full), "Buf: %lu", bufTimeMillis);
    display.drawStr(64, 8, full);

    snprintf(full, sizeof(full), "Min: %ld", this->scale->min().measuringPoint);
    display.drawStr(64, 17, full);

    snprintf(full, sizeof(full), "Max: %ld", this->scale->max().measuringPoint);
    display.drawStr(64, 26, full);

    snprintf(full, sizeof(full), "Raw: %ld", this->scale->latestValues->front().measuringPoint);
    display.drawStr(0, 17, full);

    snprintf(full, sizeof(full), "Tare: %ld", this->scale->tareValue);
    display.drawStr(0, 26, full);

    dtostrf(this->scale->calibrationValue, 2, 2, num);
    snprintf(full, sizeof(full), "Scale cal: %s", num);
    display.drawStr(0, 35, full);

    snprintf(full, sizeof(full), "Micros: %lu", micros());
    display.drawStr(0, 44, full);

    snprintf(full, sizeof(full), "Last refr: %lu", this->scale->latestRefreshed);
    display.drawStr(0, 53, full);
}

void ScaleDebugViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
    }
}

ScaleDebugViewController::ScaleDebugViewController(ScaleWrapper *scale): scale(scale) {

}