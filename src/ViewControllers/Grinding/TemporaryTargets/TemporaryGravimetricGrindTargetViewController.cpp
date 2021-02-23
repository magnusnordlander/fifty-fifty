//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "TemporaryGravimetricGrindTargetViewController.h"
#include <Utils/TextUtils.h>

TemporaryGravimetricGrindTargetViewController::TemporaryGravimetricGrindTargetViewController(Settings *settings, GravimetricGrindViewController* gravimetricGrindViewController): BaseTemporaryGrindTargetViewController(settings), gravimetricGrindViewController(gravimetricGrindViewController) {
    this->settingSensitivity = 80;
}

void TemporaryGravimetricGrindTargetViewController::render(U8G2 display) {
    float target_s = (float)this->target/1000;

    drawLargeFloatWithUnits(display, target_s, "g", 32, 3, 1);
}


void TemporaryGravimetricGrindTargetViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->target = this->settings->getGrindTargetWeight();
}

void TemporaryGravimetricGrindTargetViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->gravimetricGrindViewController->setTemporaryTarget(this->target);
        this->navigationController->push(this->gravimetricGrindViewController);
    } else if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->navigationController->pop();
    }
}

void TemporaryGravimetricGrindTargetViewController::subviewWasPopped(NavigationController *controller,
                                                          BaseViewController *viewController) {
    if (viewController == this->gravimetricGrindViewController) {
        this->navigationController->pop();
    }
}