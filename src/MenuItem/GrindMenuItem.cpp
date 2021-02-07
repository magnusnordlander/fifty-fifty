//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "GrindMenuItem.h"

GrindMenuItem::GrindMenuItem(BaseViewController *viewController, Settings* settings) : ViewControllerMenuItem("Grind?", viewController) {
    this->settings = settings;
}

std::string GrindMenuItem::getName() {
    char purge_string[25];
    float Purge_Target_Time_S = (float)(this->settings->getGrindTargetTime())/1000;
    snprintf(purge_string, sizeof(purge_string), "Grind (%d.%02d s)", (int)Purge_Target_Time_S, (int)(Purge_Target_Time_S*100)%100);

    std::string buffAsStdStr = purge_string;

    return buffAsStdStr;
}
