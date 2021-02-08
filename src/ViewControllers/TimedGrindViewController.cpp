//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "TimedGrindViewController.h"

void TimedGrindViewController::tick() {
    BaseViewController::tick();

    if (this->elapsedMillis() >= this->target_ms) {
        this->navigationController->pop();
    }
}

void TimedGrindViewController::viewWasPushed(NavigationController *controller) {
    BaseGrindViewController::viewWasPushed(controller);

    this->target_ms = this->settings->getGrindTargetTime();
}

void TimedGrindViewController::viewWillBePopped(NavigationController *controller) {
    BaseGrindViewController::viewWillBePopped(controller);

    this->target_ms = 0;
}

TimedGrindViewController::TimedGrindViewController(SsrState *ssr, Settings *settings) : BaseGrindViewController(ssr),
                                                                              settings(settings) {}
void TimedGrindViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    display.setFontMode(1);
    display.setDrawColor(2);

    display.setFont(u8g2_font_helvB12_te);
    display.drawStr(32,56, "Grinding");

    unsigned short elapsed_ms = this->elapsedMillis();
    unsigned short remaining_ms = this->target_ms - elapsed_ms;

    char time_string[25];
    snprintf(time_string, sizeof(time_string), "%d.%02d", (int)remaining_ms/1000, (int)(remaining_ms/10)%100);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
    if (remaining_ms < 10000) {
        display.drawStr(24,32,time_string);
        display.drawStr(96, 32, "s");
    } else {
        display.drawStr(8,32,time_string);
        display.drawStr(100, 32, "s");
    }


}
