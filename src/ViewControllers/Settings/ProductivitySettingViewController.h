//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_PRODUCTIVITYSETTINGVIEWCONTROLLER_H
#define GRINDER_PRODUCTIVITYSETTINGVIEWCONTROLLER_H

#include "BaseSettingViewController.h"

class ProductivitySettingViewController: public BaseSettingViewController {
public:
    using BaseSettingViewController::BaseSettingViewController;
    void render(U8G2 display) override;

protected:
    unsigned short getTargetFromSettings() override;

    void stageTargetInSettings(unsigned short target) override;
};


#endif //GRINDER_PRODUCTIVITYSETTINGVIEWCONTROLLER_H
