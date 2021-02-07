//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_POPNAVIGATIONMENUITEM_H
#define GRINDER_POPNAVIGATIONMENUITEM_H

#include "MenuItem.h"

class PopNavigationMenuItem: public MenuItem {
public:
    explicit PopNavigationMenuItem(std::string name);

    void activate(NavigationController *controller) override;
};


#endif //GRINDER_POPNAVIGATIONMENUITEM_H
