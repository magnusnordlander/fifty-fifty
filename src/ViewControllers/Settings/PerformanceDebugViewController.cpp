//
// Created by Magnus Nordlander on 2021-02-22.
//

#include <types.h>
#include <avr/dtostrf.h>
#include "PerformanceDebugViewController.h"

extern TimingStruct timings;

void PerformanceDebugViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr);

    char full[32];
    char num[10];

    dtostrf((float)timings.loop/1000., 3, 2, num);
    snprintf(full, sizeof(full), "Loop: %s ms", num);
    display.drawStr(0,8, full);

    dtostrf((float)timings.external/1000., 3, 2, num);
    snprintf(full, sizeof(full), "Extern: %s ms", num);
    display.drawStr(0,17, full);

    dtostrf((float)timings.manual/1000., 3, 2, num);
    snprintf(full, sizeof(full), "Manual: %s ms", num);
    display.drawStr(0,26, full);

    dtostrf((float)timings.rotation/1000., 3, 2, num);
    snprintf(full, sizeof(full), "Rot: %s ms", num);
    display.drawStr(0,35, full);

    dtostrf((float)timings.button/1000., 3, 2, num);
    snprintf(full, sizeof(full), "Button: %s ms", num);
    display.drawStr(0,44, full);

    dtostrf((float)timings.tick/1000., 3, 2, num);
    snprintf(full, sizeof(full), "Tick: %s ms", num);
    display.drawStr(0,53, full);
}

void PerformanceDebugViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
    }
}