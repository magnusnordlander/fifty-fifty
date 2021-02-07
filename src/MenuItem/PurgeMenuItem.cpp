//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "PurgeMenuItem.h"

PurgeMenuItem::PurgeMenuItem(BaseViewController *viewController, Settings* settings) : ViewControllerMenuItem("Purge?", viewController) {
    this->settings = settings;
}

std::string PurgeMenuItem::getName() {
    char purge_string[25];
    float Purge_Target_Time_S = (float)(this->settings->getPurgeTargetTime())/1000;
    snprintf(purge_string, sizeof(purge_string), "Purge (%d.%02d s)", (int)Purge_Target_Time_S, (int)(Purge_Target_Time_S*100)%100);

    std::string buffAsStdStr = purge_string;

    return buffAsStdStr;
}
