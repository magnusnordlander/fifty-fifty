//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_BASEGRINDVIEWCONTROLLER_H
#define GRINDER_BASEGRINDVIEWCONTROLLER_H

#include "ViewControllers/BaseViewController.h"
#include <SsrState.h>

class BaseGrindViewController: public BaseViewController {
public:
    explicit BaseGrindViewController(SsrState *ssr);

    void render(U8G2 display) override;

    void viewWasPushed(NavigationController *controller) override;

    void viewWillBePopped(NavigationController *controller) override;

    void subviewWillBePushed(NavigationController *controller, BaseViewController *) override;

protected:
    SsrState* ssr;
    unsigned long startTime;
    unsigned long elapsedMillis() const;
};


#endif //GRINDER_BASEGRINDVIEWCONTROLLER_H
