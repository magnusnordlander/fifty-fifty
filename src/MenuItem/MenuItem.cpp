//
// Created by Magnus Nordlander on 2021-02-07.
//

#include "MenuItem.h"

std::string MenuItem::getName() {
    return this->name;
}

MenuItem::MenuItem() {
    this->name = "Unnamed item";
}

void MenuItem::activate(NavigationController *) {

}
