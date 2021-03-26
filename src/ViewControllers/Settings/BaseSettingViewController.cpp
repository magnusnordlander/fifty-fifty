//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "BaseSettingViewController.h"

void BaseSettingViewController::handleRotation(int encoderDiff) {
    int amplified_encoder_diff = encoderDiff * this->settingSensitivity;

    if (amplified_encoder_diff != 0) {
        if (this->target + amplified_encoder_diff > USHRT_MAX) {
            this->target = USHRT_MAX;
        }
        else if (this->target + amplified_encoder_diff < 0) {
            this->target = 0;
        } else {
            this->target += amplified_encoder_diff;
        }
    }
}

BaseSettingViewController::BaseSettingViewController(Settings *settings) : settings(settings) {
    this->target = 0;
}

void BaseSettingViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->target = this->getTargetFromSettings();
}

void BaseSettingViewController::viewWillBePopped(NavigationController *controller) {
    this->stageTargetInSettings(this->target);
    BaseViewController::viewWillBePopped(controller);
}

unsigned short BaseSettingViewController::getTargetFromSettings() {
    return 0;
}

void BaseSettingViewController::stageTargetInSettings(unsigned short) {

}

void BaseSettingViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
    }
}
