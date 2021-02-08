//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "GrindTargetWeightSettingViewController.h"

void GrindTargetWeightSettingViewController::render(U8G2 display) {


    char productivity_string[25];
    float Productivity_S = (float)this->target/1000;
    snprintf(productivity_string, sizeof(productivity_string), "%d.%01d g", (int)Productivity_S, (int)(Productivity_S*10)%10);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
    display.drawStr(16,42,productivity_string);


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
