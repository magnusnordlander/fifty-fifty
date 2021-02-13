//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_BASESETTINGVIEWCONTROLLER_H
#define GRINDER_BASESETTINGVIEWCONTROLLER_H

#include "ViewControllers/BaseViewController.h"
#include <Settings.h>

class BaseSettingViewController: public BaseViewController {
public:
    void handleRotation(int encoderDiff) override;

    void handleButtonState(bool state) override;

    explicit BaseSettingViewController(Settings *settings);

    void viewWasPushed(NavigationController *controller) override;

    void viewWillBePopped(NavigationController *controller) override;
protected:
    virtual unsigned short getTargetFromSettings();
    virtual void stageTargetInSettings(unsigned short target);

    Settings* settings;
    unsigned short target;

    unsigned short settingSensitivity = 4;
};


#endif //GRINDER_BASESETTINGVIEWCONTROLLER_H
