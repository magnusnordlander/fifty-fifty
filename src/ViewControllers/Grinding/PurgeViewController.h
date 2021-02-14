//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_PURGEVIEWCONTROLLER_H
#define GRINDER_PURGEVIEWCONTROLLER_H

#include "BaseGrindViewController.h"
#include "Settings.h"

class PurgeViewController: public BaseGrindViewController {
public:
    PurgeViewController(SsrState *ssr, Settings *settings);

    void tick(U8G2 display) override;

    void setTemporaryTarget(unsigned long targetTime);

    void viewWasPushed(NavigationController *controller) override;
    void viewWillBePopped(NavigationController *controller) override;

    void render(U8G2 display) override;

protected:
    Settings* settings;

    unsigned long target_ms = 0;
    unsigned long temporary_target = 0;
};


#endif //GRINDER_PURGEVIEWCONTROLLER_H
