//
// Created by Magnus Nordlander on 2021-02-21.
//

#include "DebugViewController.h"

void DebugViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr);

    char full[32];
    display.drawStr(0,8, "Version: ");

    snprintf(full, sizeof(full), "Scale raw: %ld", this->scale->latestValues->front().measuringPoint);
    display.drawStr(0, 17, full);

    snprintf(full, sizeof(full), "Scale tare: %ld", this->scale->tareValue);
    display.drawStr(0, 26, full);

    snprintf(full, sizeof(full), "Scale cal: %f", this->scale->calibrationValue);
    display.drawStr(0, 35, full);

    snprintf(full, sizeof(full), "Micros: %lu", micros());
    display.drawStr(0, 44, full);

    snprintf(full, sizeof(full), "Last refr: %lu", this->scale->latestRefreshed);
    display.drawStr(0, 53, full);

    snprintf(full, sizeof(full), "Last upd: %lu", ScaleWrapper::dataReadAt);
    display.drawStr(0, 62, full);
}

void DebugViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
    }
}

DebugViewController::DebugViewController(ScaleWrapper *scale): scale(scale) {

}