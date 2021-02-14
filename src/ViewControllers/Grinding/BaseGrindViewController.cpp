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
    this->ssr->enable();
}

void BaseGrindViewController::viewWillBePopped(NavigationController *controller) {
    BaseViewController::viewWillBePopped(controller);
    this->startTime = 0;
    this->ssr->disable();
}

BaseGrindViewController::BaseGrindViewController(SsrState *ssr) : ssr(ssr) {
    this->startTime = 0;
}

unsigned long BaseGrindViewController::elapsedMillis() const {
    return millis() - this->startTime;
}

void BaseGrindViewController::subviewWillBePushed(NavigationController *controller, BaseViewController *) {
    // Remove ourselves first
    controller->pop();
}
