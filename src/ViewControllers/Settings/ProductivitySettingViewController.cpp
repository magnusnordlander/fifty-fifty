//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "ProductivitySettingViewController.h"
#include <Utils/TextUtils.h>

void ProductivitySettingViewController::render(U8G2 display) {
    drawLargeFloatWithUnits(display, (float)this->target/1000, "g/s", 42, 3, 2);
}

unsigned short ProductivitySettingViewController::getTargetFromSettings() {
    return this->settings->getProductivity();
}

void ProductivitySettingViewController::stageTargetInSettings(unsigned short target) {
    this->settings->setProductivity(target);
}
