//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "GravimetricGrindViewController.h"
#include <avr/dtostrf.h>

#define REACTION_TIME_MICROS 100000

GravimetricGrindViewController::GravimetricGrindViewController(SsrState *ssr, ScaleWrapper *scale,
                                                               Settings *settings) : BaseGrindViewController(ssr) {
    this->scale = scale;
    this->settings = settings;
}

void GravimetricGrindViewController::tick(U8G2 display) {
    if (!this->tared) {
        display.clearBuffer();
        this->renderTaringView(display);
        display.sendBuffer();

        scale->tare(10);
        this->tared = true;
    } else {
        this->ssr->enable();

        this->redraw(display);

        if (this->scale->getReactionCompensatedLatestValue(REACTION_TIME_MICROS)*1000 >= (float)(this->target_mg)) {
            this->navigationController->pop();
        }
    }
}

void GravimetricGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller); // NOLINT(bugprone-parent-virtual-call)

    this->scale->setRefreshing(true);
    this->startTime = millis();
    this->target_mg = this->settings->getGrindTargetWeight();
}

void GravimetricGrindViewController::viewWillBePopped(NavigationController *controller) {
    BaseGrindViewController::viewWillBePopped(controller);

    this->target_mg = 0;
    this->tared = false;
    this->scale->setRefreshing(false);
}

void GravimetricGrindViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,56, "Grinding");

    unsigned short ground_mg = (int)(this->scale->getLatestValue()*1000);
    unsigned short remaining_mg = this->target_mg - ground_mg;

    char time_string[25];
    dtostrf((float)(remaining_mg)/1000., 3, 1, time_string);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
    if (remaining_mg < 10000) {
        display.drawStr(40,32,time_string);
        display.drawStr(96, 32, "g");
    } else {
        display.drawStr(24,32,time_string);
        display.drawStr(100, 32, "g");
    }
}

void GravimetricGrindViewController::renderTaringView(U8G2 display) {
    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,36, "Taring...");
}
