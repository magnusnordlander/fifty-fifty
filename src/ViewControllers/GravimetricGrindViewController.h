//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_GRAVIMETRICGRINDVIEWCONTROLLER_H
#define GRINDER_GRAVIMETRICGRINDVIEWCONTROLLER_H

#include "BaseGrindViewController.h"
#include <Settings.h>
#include <ScaleWrapper.h>

class GravimetricGrindViewController: public BaseGrindViewController {
public:
    GravimetricGrindViewController(SsrState *ssr, ScaleWrapper *scale,
                                   Settings *settings);

    void tick() override;

    void viewWasPushed(NavigationController *controller) override;

    void viewWillBePopped(NavigationController *controller) override;

    void render(U8G2 display) override;

protected:
    Settings* settings;
    ScaleWrapper* scale;

    bool tared = false;

    unsigned long target_mg = 0;
};


#endif //GRINDER_GRAVIMETRICGRINDVIEWCONTROLLER_H
