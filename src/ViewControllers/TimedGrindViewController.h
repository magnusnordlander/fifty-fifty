//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_TIMEDGRINDVIEWCONTROLLER_H
#define GRINDER_TIMEDGRINDVIEWCONTROLLER_H

#include "BaseGrindViewController.h"
#include <Settings.h>

class TimedGrindViewController: public BaseGrindViewController {
public:
    TimedGrindViewController(SsrState *ssr, Settings *settings);

    void tick() override;

    void viewWasPushed(NavigationController *controller) override;

    void viewWillBePopped(NavigationController *controller) override;

    void render(U8G2 display) override;

protected:
    Settings* settings;

    unsigned long target_ms = 0;
};


#endif //GRINDER_TIMEDGRINDVIEWCONTROLLER_H
