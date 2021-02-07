//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "MenuViewController.h"

#include <utility>
#define MENU_ROW_HEIGHT 14
#define MENU_SENSITIVITY 3
#define ENCODER_SW_DEAD_TIME 200

void MenuViewController::render(U8G2 display) {
    display.clearBuffer();
    display.setFontMode(1);
    display.setDrawColor(2);
    display.setFont(u8g2_font_ncenB08_tr);

    display.drawBox(0, 2+(this->currentSelection*MENU_ROW_HEIGHT), 128, 16);

    for (size_t i = 0; i < this->menuItems.size(); ++i) {
        display.drawStr(8, (i+1)*MENU_ROW_HEIGHT, this->menuItems[i]->getName().c_str());
    }

    display.sendBuffer();
}

MenuViewController::MenuViewController(std::vector<MenuItem*> items) {
    this->menuItems = std::move(items);
}

void MenuViewController::handleRotation(int encoderDiff) {
    unsigned int numMenuItems = this->menuItems.size();

    overflow += encoderDiff;

    if (overflow > MENU_SENSITIVITY) {
        overflow = 0;
        currentSelection = (currentSelection + 1) % numMenuItems;
    }

    if (overflow < -MENU_SENSITIVITY) {
        overflow = 0;
        if (currentSelection == 0) {
            currentSelection = numMenuItems-1;
        } else {
            currentSelection = (currentSelection - 1) % numMenuItems;
        }
    }
}

void MenuViewController::handleButtonState(bool state) {
    if (state && this->navigationController) {
        this->menuItems[this->currentSelection]->activate(this->navigationController);
        delay(ENCODER_SW_DEAD_TIME);
    }
}

void MenuViewController::viewWillBePopped(NavigationController *controller) {
    BaseViewController::viewWillBePopped(controller);
    this->currentSelection = 0;
}
