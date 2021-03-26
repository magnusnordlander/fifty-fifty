//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_BASETIMESETTINGVIEWCONTROLLER_H
#define GRINDER_BASETIMESETTINGVIEWCONTROLLER_H

#include "ViewControllers/BaseViewController.h"
#include "BaseSettingViewController.h"
#include <Settings.h>
#include <NavigationController.h>

class BaseTimeSettingViewController: public BaseSettingViewController {
public:
    using BaseSettingViewController::BaseSettingViewController;

    void render(U8G2 display) override;
};


#endif //GRINDER_BASETIMESETTINGVIEWCONTROLLER_H
