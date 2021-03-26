//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_BASEVIEWCONTROLLER_H
#define GRINDER_BASEVIEWCONTROLLER_H

#include <U8g2lib.h>
#include <NavigationController.h>
#include "ButtonEvent.h"

class BaseViewController {
public:
    virtual void render(U8G2 display);
    virtual void handleRotation(int encoderDiff);
    virtual void handleButtonEvent(ButtonEvent event);

    virtual void tick(U8G2 display);

    virtual void viewWillBePushed(NavigationController *);
    virtual void viewWasPushed(NavigationController *);
    virtual void viewWillBePopped(NavigationController *);
    virtual void viewWasPopped(NavigationController *);

    virtual void subviewWillBePushed(NavigationController *, BaseViewController *);
    virtual void subviewWasPushed(NavigationController *, BaseViewController *);
    virtual void subviewWasPopped(NavigationController *, BaseViewController *);

    virtual ~BaseViewController() = default;
protected:
    NavigationController* navigationController;

    void redraw(U8G2 display);
};


#endif //GRINDER_BASEVIEWCONTROLLER_H
