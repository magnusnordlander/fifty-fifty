//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "BaseTemporaryGrindTargetViewController.h"
#include <Utils/TextUtils.h>

void BaseTemporaryGrindTargetViewController::handleRotation(int encoderDiff) {
    int amplified_encoder_diff = encoderDiff * this->settingSensitivity;

    if (amplified_encoder_diff != 0) {
        if (this->target + amplified_encoder_diff > USHRT_MAX) {
            this->target = USHRT_MAX;
        }
        else if (this->target + amplified_encoder_diff < 0) {
            this->target = 0;
        } else {
            this->target += amplified_encoder_diff;
        }
    }
}

BaseTemporaryGrindTargetViewController::BaseTemporaryGrindTargetViewController(Settings *settings) : settings(settings) {}
