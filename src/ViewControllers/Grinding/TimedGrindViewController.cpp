//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "TimedGrindViewController.h"
#include <Utils/TextUtils.h>

void TimedGrindViewController::tick(U8G2 display) {
    BaseGrindViewController::tick(display);

    if (this->elapsedMillis() >= this->target_ms) {
        this->grinding = false;
        this->navigationController->pop();
    }
}

void TimedGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseGrindViewController::viewWasPushed(controller);

    if (this->temporary_target > 0) {
        this->target_ms = this->temporary_target;
    } else {
        this->target_ms = this->settings->getGrindTargetTime();
    }
}

void TimedGrindViewController::viewWillBePopped(NavigationController *controller) {
    BaseGrindViewController::viewWillBePopped(controller);

    this->target_ms = 0;
}

TimedGrindViewController::TimedGrindViewController(SsrState *ssr, Settings *settings, ScaleWrapper* scale) : BaseGrindViewController(ssr, settings, scale) {}

void TimedGrindViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,56, "Grinding");

    unsigned short elapsed_ms = this->elapsedMillis();
    unsigned short remaining_ms = this->target_ms - elapsed_ms;

    drawLargeFloatWithUnits(display, (float)(remaining_ms)/1000, "s", 32, 3, 2);
}

GrindType TimedGrindViewController::getGrindType() {
    return grindByTime;
}
