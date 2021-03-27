//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "BaseGrindViewController.h"
#include <Model/GrindSession.h>
#include "Utils/SessionSender.h"

#define VECTOR_SIZE 100

std::vector<MeasuringPoint>* sharedMeasuringPoints = new std::vector<MeasuringPoint>;

void BaseGrindViewController::render(U8G2 display) {
    BaseViewController::render(display);
}

void BaseGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->startTime = millis();
    this->grinding = true;
}

void BaseGrindViewController::viewWillBePopped(NavigationController *controller) {
    if (this->stopTime == 0) {
        this->stopTime = millis();
    }

    GrindSession gs{};
    gs.settings = settings;
    gs.startTime = this->startTime;
    gs.endTime = this->stopTime;
    gs.type = getGrindType();
    gs.tareValue = scale->tareValue;
    gs.temporaryTarget = temporary_target;

    BaseViewController::viewWillBePopped(controller);

    this->startTime = 0;
    this->stopTime = 0;
    this->temporary_target = 0;
    this->grinding = false;
    this->ssr->disable();

    sendSession(gs, sharedMeasuringPoints);

    sharedMeasuringPoints->clear();
}

BaseGrindViewController::BaseGrindViewController(SsrState *ssr, Settings* settings, ScaleWrapper* scale) : settings(settings), scale(scale), ssr(ssr) {
    this->startTime = 0;
}

void BaseGrindViewController::setTemporaryTarget(millitime_t target) {
    this->temporary_target = target;
}


millitime_t BaseGrindViewController::elapsedMillis() const {
    return millis() - this->startTime;
}

void BaseGrindViewController::subviewWillBePushed(NavigationController *controller, BaseViewController *) {
    // Remove ourselves first
    controller->pop();
}

void BaseGrindViewController::tick(U8G2 display) {
    millitime_t now = millis();

    if (this->grinding) {
        this->stopTime = 0;
        this->ssr->enable();
    } else {
        if (this->stopTime == 0) {
            this->stopTime = now;
        }
        this->ssr->disable();
    }

    if (now - lastMP > 200 && (this->stopTime == 0 || now - this->stopTime < 2000) && sharedMeasuringPoints->size() < VECTOR_SIZE) {
        lastMP = now;
        sharedMeasuringPoints->push_back(scale->latestAverage(80));
    }

    BaseViewController::tick(display);
}

GrindType BaseGrindViewController::getGrindType() {
    return manual;
}

void BaseGrindViewController::initShared() {
    sharedMeasuringPoints->reserve(VECTOR_SIZE);
}
