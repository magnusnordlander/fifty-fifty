//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "GravimetricGrindViewController.h"
#include <avr/dtostrf.h>
#include <Utils/TextUtils.h>

GravimetricGrindViewController::GravimetricGrindViewController(SsrState *ssr, ScaleWrapper *scale,
                                                               Settings *settings) : BaseGrindViewController(ssr) {
    this->scale = scale;
    this->settings = settings;
    this->progressBar = new ProgressBarView;
}

void GravimetricGrindViewController::tick(U8G2 display) {
    BaseGrindViewController::tick(display);

    if (this->taring && this->scale->getTareStatus()) {
        this->taring = false;
        this->grinding = true;
    }

    if (!this->taring && !this->done) {
        if (this->scale->getReactionCompensatedLatestValue(this->reaction_time)*1000 >= (float)(this->target_mg)) {
            this->grinding = false;
            this->done = true;
        }
    }
}

void GravimetricGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller); // NOLINT(bugprone-parent-virtual-call)

    this->startTime = millis();
    this->done = false;

    if (this->temporary_target > 0) {
        this->target_mg = this->temporary_target;
    } else {
        this->target_mg = this->settings->getGrindTargetWeight();
    }

    this->reaction_time = this->settings->getReactionTime();
    this->startTare();
}

void GravimetricGrindViewController::viewWillBePopped(NavigationController *controller) {
    BaseGrindViewController::viewWillBePopped(controller);

    this->target_mg = 0;
    this->reaction_time = 0;
    this->done = false;
}

void GravimetricGrindViewController::render(U8G2 display) {
    if (this->taring) {
        this->renderTaringView(display);
    } else {
        this->renderGrindingView(display);
    }
}

void GravimetricGrindViewController::renderGrindingView(U8G2 display) {
    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);

    unsigned int ground_mg = (int)(this->scale->getLatestValue()*1000);
    signed int remaining_mg = this->target_mg - ground_mg;

    if (this->done) {
        display.drawStr(40,56, "Done");
        drawLargeFloatWithUnits(display, (float)(ground_mg)/1000., "g", 32, 5, 1);
    } else {
        display.drawStr(32,56, "Grinding");
        drawLargeFloatWithUnits(display, (float)(remaining_mg)/1000., "g", 32, 5, 1);
    }
}

void GravimetricGrindViewController::renderTaringView(U8G2 display) {
    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,36, "Taring...");

    this->progressBar->drawRelative(display, 14, 54);
}

void GravimetricGrindViewController::startTare() {
    this->taring = true;
    this->scale->tareNoDelay();
}

GravimetricGrindViewController::~GravimetricGrindViewController() {
    delete this->progressBar;
}

void GravimetricGrindViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
    }
}
