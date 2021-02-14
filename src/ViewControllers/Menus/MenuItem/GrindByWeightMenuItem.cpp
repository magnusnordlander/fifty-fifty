//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "GrindByWeightMenuItem.h"
#include <avr/dtostrf.h>

GrindByWeightMenuItem::GrindByWeightMenuItem(BaseViewController *viewController, Settings* settings) : ViewControllerMenuItem("Grind?", viewController) {
    this->settings = settings;
}

std::string GrindByWeightMenuItem::getName() {
    char weight_string[6];
    dtostrf((float)(this->settings->getGrindTargetWeight())/1000., 3, 1, weight_string);

    char purge_string[25];
    snprintf(purge_string, sizeof(purge_string), "Grind (%s g)", weight_string);

    std::string buffAsStdStr = purge_string;

    return buffAsStdStr;
}
