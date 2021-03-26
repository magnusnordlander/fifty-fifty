//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_PURGETIMESETTINGVIEWCONTROLLER_H
#define GRINDER_PURGETIMESETTINGVIEWCONTROLLER_H

#include "BaseTimeSettingViewController.h"

class PurgeTimeSettingViewController: public BaseTimeSettingViewController {
public:
    using BaseTimeSettingViewController::BaseTimeSettingViewController;
protected:
    unsigned short getTargetFromSettings() override;

    void stageTargetInSettings(unsigned short time) override;
};


#endif //GRINDER_PURGETIMESETTINGVIEWCONTROLLER_H
