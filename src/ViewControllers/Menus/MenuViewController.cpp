//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "MenuViewController.h"

#include <utility>
#define MENU_ROW_HEIGHT 14

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

    microtime_t timeDiff = micros() - lastScrollEvent;

    bool direction = encoderDiff > 0;
    if (direction != lastDirection && timeDiff <= MENU_SCROLL_DEAD_TIME_DIRECTION_SWITCH) {
        return;
    }

    microtime_t deadTime = MENU_SCROLL_DEAD_TIME_MICROS;

    if (abs(encoderDiff) >= MENU_DOUBLE_SCROLL_THRESHOLD) {
        deadTime = MENU_SCROLL_DOUBLE_SCROLL_DEAD_TIME_MICROS;
    }

    if (timeDiff >= deadTime) {
        unsigned short steps = 1;

        if (direction) {
            currentSelection = (currentSelection + steps) % numMenuItems;
        } else {
            if (currentSelection == 0) {
                currentSelection = numMenuItems - steps;
            } else {
                currentSelection = (currentSelection - steps) % numMenuItems;
            }
        }

        lastScrollEvent = micros();
        lastDirection = direction;
    }
}

void MenuViewController::viewWillBePopped(NavigationController *controller) {
    BaseViewController::viewWillBePopped(controller);
    this->currentSelection = 0;
}

void MenuViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->menuItems[this->currentSelection]->activate(this->navigationController);
    } else if (event == BUTTON_PRESS_AND_HOLD_LET_UP) {
        this->menuItems[this->currentSelection]->activatePressAndHold(this->navigationController);
    }
}
