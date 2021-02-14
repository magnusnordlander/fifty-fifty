//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "BaseTimeSettingViewController.h"
#include <Utils/TextUtils.h>

void BaseTimeSettingViewController::render(U8G2 display) {
    float target_s = (float)this->target/1000;

    drawLargeFloatWithUnits(display, target_s, "s", 32, 3, 2);
    drawWeightApproximation(display, (target_s * ((float)(this->settings->getProductivity())/1000)), 56);
}
