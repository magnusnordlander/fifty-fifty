//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_GRINDTIMESETTINGVIEWCONTROLLER_H
#define GRINDER_GRINDTIMESETTINGVIEWCONTROLLER_H

#include "BaseTimeSettingViewController.h"

class GrindTimeSettingViewController: public BaseTimeSettingViewController {
public:
    using BaseTimeSettingViewController::BaseTimeSettingViewController;
protected:
    unsigned short getTargetFromSettings() override;
    void stageTargetInSettings(unsigned short time) override;
};


#endif //GRINDER_GRINDTIMESETTINGVIEWCONTROLLER_H
