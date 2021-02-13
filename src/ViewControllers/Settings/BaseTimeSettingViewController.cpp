//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "BaseTimeSettingViewController.h"

void BaseTimeSettingViewController::render(U8G2 display) {


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
