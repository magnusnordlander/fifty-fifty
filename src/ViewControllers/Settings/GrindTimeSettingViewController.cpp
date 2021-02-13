//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "GrindTimeSettingViewController.h"

unsigned short GrindTimeSettingViewController::getTargetFromSettings() {
    return this->settings->getGrindTargetTime();
}

void GrindTimeSettingViewController::stageTargetInSettings(unsigned short time) {
    this->settings->setGrindTargetTime(time);
}