//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_TEMPORARYGRAVIMETRICGRINDTARGETVIEWCONTROLLER_H
#define GRINDER_TEMPORARYGRAVIMETRICGRINDTARGETVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Model/Settings.h>
#include <ViewControllers/Grinding/GravimetricGrindViewController.h>
#include "BaseTemporaryGrindTargetViewController.h"

class TemporaryGravimetricGrindTargetViewController: public BaseTemporaryGrindTargetViewController {
public:
    explicit TemporaryGravimetricGrindTargetViewController(Settings *settings, GravimetricGrindViewController* gravimetricGrindViewController);

    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;

    void viewWasPushed(NavigationController *controller) override;

    void subviewWasPopped(NavigationController *controller, BaseViewController *viewController) override;

protected:
    GravimetricGrindViewController* gravimetricGrindViewController;
};

#endif //GRINDER_TEMPORARYGRAVIMETRICGRINDTARGETVIEWCONTROLLER_H
