//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "TemporaryPurgeTargetViewController.h"
#include <Utils/TextUtils.h>

TemporaryPurgeTargetViewController::TemporaryPurgeTargetViewController(Settings *settings, PurgeViewController* purgeViewController): BaseTemporaryGrindTargetViewController(settings), purgeViewController(purgeViewController) {
}

void TemporaryPurgeTargetViewController::render(U8G2 display) {
    float target_s = (float)this->target/1000;

    drawLargeFloatWithUnits(display, target_s, "s", 32, 3, 2);
    drawWeightApproximation(display, (target_s * ((float)(this->settings->getProductivity())/1000)), 56);
}


void TemporaryPurgeTargetViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->target = this->settings->getPurgeTargetTime();
}

void TemporaryPurgeTargetViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->purgeViewController->setTemporaryTarget(this->target);
        this->navigationController->push(this->purgeViewController);
    } else if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->navigationController->pop();
    }
}

void TemporaryPurgeTargetViewController::subviewWasPopped(NavigationController *controller,
                                                          BaseViewController *viewController) {
    if (viewController == this->purgeViewController) {
        this->navigationController->pop();
    }
}