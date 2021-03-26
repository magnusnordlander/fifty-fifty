//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "PopNavigationAndCommitEEPROMMenuItem.h"

void PopNavigationAndCommitEEPROMMenuItem::activate(NavigationController *controller) {
    PopNavigationMenuItem::activate(controller);

    this->settings->commitToEEPROM();
}

PopNavigationAndCommitEEPROMMenuItem::PopNavigationAndCommitEEPROMMenuItem(const std::string& name, Settings *settings): PopNavigationMenuItem(name) {
    this->settings = settings;
}
