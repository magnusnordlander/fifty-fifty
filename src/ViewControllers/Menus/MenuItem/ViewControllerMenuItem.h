//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_MENUVIEWCONTROLLERVIEWITEM_H
#define GRINDER_MENUVIEWCONTROLLERVIEWITEM_H

#include "MenuItem.h"
#include "ViewControllers/BaseViewController.h"

class ViewControllerMenuItem: public MenuItem {
public:
    std::string getName() override;

    ViewControllerMenuItem(std::string name, BaseViewController *viewController);

    void activate(NavigationController *controller) override;

private:
    BaseViewController* viewController;
};


#endif //GRINDER_MENUVIEWCONTROLLERVIEWITEM_H
