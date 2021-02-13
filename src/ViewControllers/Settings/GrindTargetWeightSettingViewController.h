//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_GRINDTARGETWEIGHTSETTINGVIEWCONTROLLER_H
#define GRINDER_GRINDTARGETWEIGHTSETTINGVIEWCONTROLLER_H

#include "BaseSettingViewController.h"

class GrindTargetWeightSettingViewController: public BaseSettingViewController {
public:
    GrindTargetWeightSettingViewController(Settings *settings);

    void render(U8G2 display) override;

protected:
    unsigned short getTargetFromSettings() override;

    void stageTargetInSettings(unsigned short target) override;
};

#endif //GRINDER_GRINDTARGETWEIGHTSETTINGVIEWCONTROLLER_H
