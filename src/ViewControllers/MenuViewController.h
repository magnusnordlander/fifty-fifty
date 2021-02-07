//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_MENUVIEWCONTROLLER_H
#define GRINDER_MENUVIEWCONTROLLER_H

#include <vector>
#include "BaseViewController.h"
#include "../MenuItem/MenuItem.h"

class MenuViewController: public BaseViewController {
public:
    explicit MenuViewController(std::vector<MenuItem*> menuItems);

    void render(U8G2 display) override;

    void handleRotation(int encoderDiff) override;
    void handleButtonState(bool state) override;

    void viewWillBePopped(NavigationController *controller) override;

private:
    unsigned short translateYCoordinate(unsigned short coordinate) const;

    std::vector<MenuItem*> menuItems;

    unsigned short currentSelection = 0;
    short overflow = 0;
};


#endif //GRINDER_MENUVIEWCONTROLLER_H
