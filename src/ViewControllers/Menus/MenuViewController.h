//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_MENUVIEWCONTROLLER_H
#define GRINDER_MENUVIEWCONTROLLER_H

#include <vector>
#include "ViewControllers/BaseViewController.h"
#include "MenuItem/MenuItem.h"
#include <types.h>

#define MENU_SCROLL_DEAD_TIME_MICROS 120000
#define MENU_SCROLL_DOUBLE_SCROLL_DEAD_TIME_MICROS 30000
#define MENU_SCROLL_DEAD_TIME_DIRECTION_SWITCH 500000
#define MENU_DOUBLE_SCROLL_THRESHOLD 5

class MenuViewController: public BaseViewController {
public:
    explicit MenuViewController(std::vector<MenuItem*> menuItems);

    void render(U8G2 display) override;

    void handleRotation(int encoderDiff) override;
    void handleButtonEvent(ButtonEvent event) override;

    void viewWillBePopped(NavigationController *controller) override;

private:
    unsigned short translateYCoordinate(unsigned short coordinate) const;

    std::vector<MenuItem*> menuItems;

    unsigned short currentSelection = 0;
    short overflow = 0;

    microtime_t lastScrollEvent = 0;
    bool lastDirection = true;
};


#endif //GRINDER_MENUVIEWCONTROLLER_H
