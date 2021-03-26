//
// Created by Magnus Nordlander on 2021-02-13.
//

#ifndef GRINDER_REACTIONTIMESETTINGVIEWCONTROLLER_H
#define GRINDER_REACTIONTIMESETTINGVIEWCONTROLLER_H

#include "BaseTimeSettingViewController.h"

class ReactionTimeSettingViewController: public BaseTimeSettingViewController {
public:
    using BaseTimeSettingViewController::BaseTimeSettingViewController;
protected:
    unsigned short getTargetFromSettings() override;

    void stageTargetInSettings(unsigned short time) override;
};


#endif //GRINDER_REACTIONTIMESETTINGVIEWCONTROLLER_H
