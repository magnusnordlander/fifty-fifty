//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "ProductivitySettingViewController.h"

void ProductivitySettingViewController::render(U8G2 display) {
    display.clearBuffer();

    char productivity_string[25];
    float Productivity_S = (float)this->target/1000;
    snprintf(productivity_string, sizeof(productivity_string), "%d.%02d g/s", (int)Productivity_S, (int)(Productivity_S*100)%100);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
    display.drawStr(8,42,productivity_string);

    display.sendBuffer();
}

unsigned short ProductivitySettingViewController::getTargetFromSettings() {
    return this->settings->getProductivity();
}

void ProductivitySettingViewController::stageTargetInSettings(unsigned short target) {
    this->settings->setProductivity(target);
}
