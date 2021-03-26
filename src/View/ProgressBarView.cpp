//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "ProgressBarView.h"

void ProgressBarView::drawRelative(U8G2 display, unsigned short x, unsigned short y) {
    unsigned short doublemilli = (micros() / 1000) % 2000;

    // Goes between 0 and 74
    unsigned short frame = doublemilli / 27;

    unsigned short start;
    unsigned short width;

    if (frame <= 25) {
        start = x;
        width = 2 * frame;
    } else if (frame <= 50) {
        start = x + (frame - 25) * 2;
        width = 50;
    } else {
        start = x + (frame - 25) * 2;
        width = 50 - (frame - 50) * 2;
    }

    display.drawBox(start, y, width, 5);
}
