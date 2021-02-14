//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "GrindTargetWeightSettingViewController.h"
#include <Utils/TextUtils.h>

void GrindTargetWeightSettingViewController::render(U8G2 display) {
    drawLargeFloatWithUnits(display, (float)this->target/1000, "g", 42);
}

unsigned short GrindTargetWeightSettingViewController::getTargetFromSettings() {
    return this->settings->getGrindTargetWeight();
}

void GrindTargetWeightSettingViewController::stageTargetInSettings(unsigned short target) {
    this->settings->setGrindTargetWeight(target);
}

GrindTargetWeightSettingViewController::GrindTargetWeightSettingViewController(Settings *settings)
        : BaseSettingViewController(settings) {
    this->settingSensitivity = 20;
}
