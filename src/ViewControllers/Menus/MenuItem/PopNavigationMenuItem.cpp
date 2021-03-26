//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "PopNavigationMenuItem.h"
#include <utility>

PopNavigationMenuItem::PopNavigationMenuItem(std::string name) {
    this->name = std::move(name);
}

void PopNavigationMenuItem::activate(NavigationController *controller) {
    controller->pop();
}
