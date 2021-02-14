//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_TEMPORARYPURGETARGETVIEWCONTROLLER_H
#define GRINDER_TEMPORARYPURGETARGETVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Settings.h>
#include <ViewControllers/Grinding/PurgeViewController.h>

class TemporaryPurgeTargetViewController: public BaseViewController {
public:
    explicit TemporaryPurgeTargetViewController(Settings *settings, PurgeViewController* purgeViewController);

    void render(U8G2 display) override;

    void handleRotation(int encoderDiff) override;

    void handleButtonEvent(ButtonEvent event) override;

    void viewWasPushed(NavigationController *controller) override;

    void subviewWasPopped(NavigationController *controller, BaseViewController *viewController) override;

protected:
    unsigned short target = 0;
    unsigned short settingSensitivity = 4;
    Settings* settings;
    PurgeViewController* purgeViewController;
};


#endif //GRINDER_TEMPORARYPURGETARGETVIEWCONTROLLER_H
