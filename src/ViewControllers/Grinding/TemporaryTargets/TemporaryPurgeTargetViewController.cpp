//
// Created by Magnus Nordlander on 2021-02-14.
//

#include "TemporaryPurgeTargetViewController.h"

void TemporaryPurgeTargetViewController::render(U8G2 display) {
    char purge_string[25];
    float target_s = (float)this->target/1000;

    snprintf(purge_string, sizeof(purge_string), "%d.%02d s", (int)target_s, (int)(target_s*100)%100);

    display.setFont(u8g2_font_logisoso24_tr); // choose a suitable font
    display.drawStr(24,32,purge_string);

    display.setFont(u8g2_font_ncenB08_tr);

    char target_weight_string[25];
    float Target_Weight_G = (target_s * ((float)(this->settings->getProductivity())/1000));
    snprintf(target_weight_string, sizeof(target_weight_string), "Approx. %d.%02d g", (int)Target_Weight_G, (int)(Target_Weight_G*100)%100);
    display.drawStr(0, 56, target_weight_string);
}

void TemporaryPurgeTargetViewController::handleRotation(int encoderDiff) {
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

TemporaryPurgeTargetViewController::TemporaryPurgeTargetViewController(Settings *settings, PurgeViewController* purgeViewController) : settings(settings), purgeViewController(purgeViewController) {
}

void TemporaryPurgeTargetViewController::viewWasPushed(NavigationController *controller) {
    BaseViewController::viewWasPushed(controller);
    this->target = this->settings->getPurgeTargetTime();
}

void TemporaryPurgeTargetViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->purgeViewController->setTemporaryTarget(this->target);
        this->navigationController->push(this->purgeViewController);
    } else if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->navigationController->pop();
    }
}

void TemporaryPurgeTargetViewController::subviewWasPopped(NavigationController *controller,
                                                          BaseViewController *viewController) {
    if (viewController == this->purgeViewController) {
        this->navigationController->pop();
    }
}
