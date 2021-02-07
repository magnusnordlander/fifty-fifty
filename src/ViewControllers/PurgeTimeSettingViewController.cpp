//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "PurgeTimeSettingViewController.h"

unsigned short PurgeTimeSettingViewController::getTargetFromSettings() {
    return this->settings->getPurgeTargetTime();
}

void PurgeTimeSettingViewController::stageTargetInSettings(unsigned short time) {
    this->settings->setPurgeTargetTime(time);
}
