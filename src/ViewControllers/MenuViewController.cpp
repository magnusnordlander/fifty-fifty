//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "MenuViewController.h"

#include <utility>
#define MENU_ROW_HEIGHT 14
#define MENU_SENSITIVITY 3
#define ENCODER_SW_DEAD_TIME 200

void MenuViewController::render(U8G2 display) {

    display.setFontMode(1);
    display.setDrawColor(2);
    display.setFont(u8g2_font_ncenB08_tr);

    unsigned int numMenuItems = this->menuItems.size();

    unsigned short boxWidth = 128;
    if (numMenuItems > 4) {
        boxWidth = 122;
    }

    display.drawBox(0, this->translateYCoordinate(2+(this->currentSelection*MENU_ROW_HEIGHT)), boxWidth, 16);

    for (size_t i = 0; i < this->menuItems.size(); ++i) {
        display.drawStr(8, this->translateYCoordinate((i+1)*MENU_ROW_HEIGHT), this->menuItems[i]->getName().c_str());
    }

    if (numMenuItems > 4) {
        display.setDrawColor(1);

        auto scrollBarHeight = (unsigned int)(64. * (4. / (float)numMenuItems));
        auto scrollBarNega = (float)(64 - scrollBarHeight);
        float factor = (float)this->currentSelection / (float)(numMenuItems - 1);
        auto scrollBarY = (unsigned int)(scrollBarNega * factor);

        display.drawRBox(124, scrollBarY, 4, scrollBarHeight, 1);
    }


}

unsigned short MenuViewController::translateYCoordinate(unsigned short coordinate) const {
    if ((this->currentSelection+1)*MENU_ROW_HEIGHT < MENU_ROW_HEIGHT*3) {
        return coordinate;
    }

    return coordinate - (this->currentSelection-2)*MENU_ROW_HEIGHT;
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

void MenuViewController::viewWillBePopped(NavigationController *controller) {
    BaseViewController::viewWillBePopped(controller);
    this->currentSelection = 0;
}

void MenuViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->menuItems[this->currentSelection]->activate(this->navigationController);
    }
}
