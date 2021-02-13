//
// Created by Magnus Nordlander on 2021-02-13.
//

#include "ReactionTimeSettingViewController.h"

unsigned short ReactionTimeSettingViewController::getTargetFromSettings() {
    return this->settings->getReactionTime();
}

void ReactionTimeSettingViewController::stageTargetInSettings(unsigned short time) {
    this->settings->setReactionTime(time);
}
