//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "GrindByWeightMenuItem.h"
#include <avr/dtostrf.h>
#include <ViewControllers/Grinding/TemporaryTargets/TemporaryGravimetricGrindTargetViewController.h>

GrindByWeightMenuItem::GrindByWeightMenuItem(GravimetricGrindViewController *viewController, Settings* settings) : ViewControllerMenuItem("Grind?", viewController) {
    this->settings = settings;
    this->secondaryViewController = new TemporaryGravimetricGrindTargetViewController(settings, viewController);
}

std::string GrindByWeightMenuItem::getName() {
    char weight_string[6];
    dtostrf((float)(this->settings->getGrindTargetWeight())/1000., 3, 1, weight_string);

    char purge_string[25];
    snprintf(purge_string, sizeof(purge_string), "Grind (%s g)", weight_string);

    std::string buffAsStdStr = purge_string;

    return buffAsStdStr;
}

GrindByWeightMenuItem::~GrindByWeightMenuItem() {
    delete this->secondaryViewController;
}
