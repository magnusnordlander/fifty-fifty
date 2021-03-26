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
    ViewControllerMenuItem(std::string name, BaseViewController *viewController, BaseViewController *secondaryViewController);

    void activate(NavigationController *controller) override;

    void activatePressAndHold(NavigationController *controller) override;
protected:
    BaseViewController* viewController;
    BaseViewController* secondaryViewController = nullptr;
};


#endif //GRINDER_MENUVIEWCONTROLLERVIEWITEM_H
