//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "ViewControllerMenuItem.h"

#include <utility>

ViewControllerMenuItem::ViewControllerMenuItem(std::string name, BaseViewController *viewController) :
                                                                                                       viewController(
                                                                                                               viewController) {
    this->name = std::move(name);
}

std::string ViewControllerMenuItem::getName() {
    return name;
}

void ViewControllerMenuItem::activate(NavigationController *controller) {
    controller->push(this->viewController);
}

