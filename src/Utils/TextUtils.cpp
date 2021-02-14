//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "TextUtils.h"
#include <avr/dtostrf.h>

void drawLargeFloatWithUnits(U8G2 display, float target, const char *unit, unsigned short y, signed char width, unsigned char prec) {
    char targetAsString[25];
    dtostrf(target, width, prec, targetAsString);

    char full[25];
    snprintf(full, sizeof(full), "%s %s", targetAsString, unit);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font

    unsigned short x;
    switch (strlen(full)) {
        case 5:
            x = 24;
            break;
        case 6:
            x = 16;
            break;
        case 7:
            x = 8;
            break;
        default:
            x = 0;
            break;
    }

    display.drawStr(x, y, full);
}

void drawWeightApproximation(U8G2 display, float target_weight, unsigned short y) {
    display.setFont(u8g2_font_ncenB08_tr);

    char weight_as_string[10];
    dtostrf(target_weight, 3, 1, weight_as_string);
    char target_weight_string[25];
    snprintf(target_weight_string, sizeof(target_weight_string), "Approx. %s g", weight_as_string);
    display.drawStr(0, y, target_weight_string);
}