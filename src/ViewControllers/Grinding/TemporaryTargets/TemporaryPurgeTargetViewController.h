//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_TEMPORARYPURGETARGETVIEWCONTROLLER_H
#define GRINDER_TEMPORARYPURGETARGETVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Model/Settings.h>
#include <ViewControllers/Grinding/PurgeViewController.h>
#include "BaseTemporaryGrindTargetViewController.h"

class TemporaryPurgeTargetViewController: public BaseTemporaryGrindTargetViewController {
public:
    explicit TemporaryPurgeTargetViewController(Settings *settings, PurgeViewController* purgeViewController);

    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;

    void viewWasPushed(NavigationController *controller) override;

    void subviewWasPopped(NavigationController *controller, BaseViewController *viewController) override;

protected:
    PurgeViewController* purgeViewController;
};


#endif //GRINDER_TEMPORARYPURGETARGETVIEWCONTROLLER_H
