//
// Created by Magnus Nordlander on 2021-02-07.
//

#include <ViewControllers/Grinding/TemporaryTargets/TemporaryTimedGrindTargetViewController.h>
#include "GrindMenuItem.h"

GrindMenuItem::GrindMenuItem(TimedGrindViewController *viewController, Settings* settings) : ViewControllerMenuItem("Grind?", viewController) {
    this->settings = settings;
    this->secondaryViewController = new TemporaryTimedGrindTargetViewController(settings, viewController);
}

std::string GrindMenuItem::getName() {
    char purge_string[25];
    float Purge_Target_Time_S = (float)(this->settings->getGrindTargetTime())/1000;
    snprintf(purge_string, sizeof(purge_string), "Grind (%d.%02d s)", (int)Purge_Target_Time_S, (int)(Purge_Target_Time_S*100)%100);

    std::string buffAsStdStr = purge_string;

    return buffAsStdStr;
}

GrindMenuItem::~GrindMenuItem() {
    delete this->secondaryViewController;
}
