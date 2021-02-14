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
    this->redraw(display);

    if (this->taring && this->scale->getTareStatus()) {
        this->taring = false;
    }

    if (!this->taring) {
        this->ssr->enable();

        if (this->scale->getReactionCompensatedLatestValue(this->reaction_time)*1000 >= (float)(this->target_mg)) {
            this->navigationController->pop();
        }
    }
}

void GravimetricGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller); // NOLINT(bugprone-parent-virtual-call)

    this->startTime = millis();

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
}

void GravimetricGrindViewController::render(U8G2 display) {
    if (this->taring) {
        this->renderTaringView(display);
    } else {
        this->renderGrindingView(display);
    }
}

void GravimetricGrindViewController::renderGrindingView(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,56, "Grinding");

    unsigned short ground_mg = (int)(this->scale->getLatestValue()*1000);
    unsigned short remaining_mg = this->target_mg - ground_mg;

    drawLargeFloatWithUnits(display, (float)(remaining_mg)/1000., "g", 32, 3, 2);
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
