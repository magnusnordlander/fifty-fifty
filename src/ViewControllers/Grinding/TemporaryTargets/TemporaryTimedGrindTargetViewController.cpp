//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "TemporaryTimedGrindTargetViewController.h"
#include <Utils/TextUtils.h>

TemporaryTimedGrindTargetViewController::TemporaryTimedGrindTargetViewController(Settings *settings, TimedGrindViewController* timedGrindViewController): BaseTemporaryGrindTargetViewController(settings), timedGrindViewController(timedGrindViewController) {
}

void TemporaryTimedGrindTargetViewController::render(U8G2 display) {
    float target_s = (float)this->target/1000;

    drawLargeFloatWithUnits(display, target_s, "s", 32, 3, 2);
    drawWeightApproximation(display, (target_s * ((float)(this->settings->getProductivity())/1000)), 56);
}

void TemporaryTimedGrindTargetViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->target = this->settings->getGrindTargetTime();
}

void TemporaryTimedGrindTargetViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->timedGrindViewController->setTemporaryTarget(this->target);
        this->navigationController->push(this->timedGrindViewController);
    } else if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->navigationController->pop();
    }
}

void TemporaryTimedGrindTargetViewController::subviewWasPopped(NavigationController *controller,
                                                          BaseViewController *viewController) {
    if (viewController == this->timedGrindViewController) {
        this->navigationController->pop();
    }
}