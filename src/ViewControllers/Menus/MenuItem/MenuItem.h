//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_MENUITEM_H
#define GRINDER_MENUITEM_H

#include <string>
#include <NavigationController.h>

class MenuItem {
public:
    MenuItem();
    virtual std::string getName();
    virtual void activate(NavigationController*);
    virtual void activatePressAndHold(NavigationController *);
protected:
    std::string name;
};


#endif //GRINDER_MENUITEM_H
