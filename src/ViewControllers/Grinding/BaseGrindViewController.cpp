//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "BaseGrindViewController.h"

void BaseGrindViewController::render(U8G2 display) {
    BaseViewController::render(display);
}

void BaseGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->startTime = millis();
    this->grinding = true;
}

void BaseGrindViewController::viewWillBePopped(NavigationController *controller) {
    BaseViewController::viewWillBePopped(controller);
    this->startTime = 0;
    this->temporary_target = 0;
    this->grinding = false;
    this->ssr->disable();
}

BaseGrindViewController::BaseGrindViewController(SsrState *ssr) : ssr(ssr) {
    this->startTime = 0;
}

void BaseGrindViewController::setTemporaryTarget(unsigned long target) {
    this->temporary_target = target;
}


unsigned long BaseGrindViewController::elapsedMillis() const {
    return millis() - this->startTime;
}

void BaseGrindViewController::subviewWillBePushed(NavigationController *controller, BaseViewController *) {
    // Remove ourselves first
    controller->pop();
}

void BaseGrindViewController::tick(U8G2 display) {
    if (this->grinding) {
        this->ssr->enable();
    } else {
        this->ssr->disable();
    }

    BaseViewController::tick(display);
}
