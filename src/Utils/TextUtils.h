//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_TEXTUTILS_H
#define GRINDER_TEXTUTILS_H

#include <U8g2lib.h>

void drawLargeFloatWithUnits(U8G2 display, float target, const char* unit, unsigned short y, signed char width = 3, unsigned char prec = 1);
void drawWeightApproximation(U8G2 display, float target, unsigned short y);
void drawStabilityMarker(U8G2 display);
void drawGrindRate(U8G2 display, float rate, unsigned short y);

#endif //GRINDER_TEXTUTILS_H
