//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_TEMPORARYTIMEDGRINDTARGETVIEWCONTROLLER_H
#define GRINDER_TEMPORARYTIMEDGRINDTARGETVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Settings.h>
#include <ViewControllers/Grinding/TimedGrindViewController.h>
#include "BaseTemporaryGrindTargetViewController.h"

class TemporaryTimedGrindTargetViewController: public BaseTemporaryGrindTargetViewController {
public:
    explicit TemporaryTimedGrindTargetViewController(Settings *settings, TimedGrindViewController* timedGrindViewController);

    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;

    void viewWasPushed(NavigationController *controller) override;

    void subviewWasPopped(NavigationController *controller, BaseViewController *viewController) override;

protected:
    TimedGrindViewController* timedGrindViewController;
};

#endif //GRINDER_TEMPORARYTIMEDGRINDTARGETVIEWCONTROLLER_H
