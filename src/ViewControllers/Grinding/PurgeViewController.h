//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_PURGEVIEWCONTROLLER_H
#define GRINDER_PURGEVIEWCONTROLLER_H

#include "BaseGrindViewController.h"
#include "Model/Settings.h"
#include <types.h>

class PurgeViewController: public BaseGrindViewController {
public:
    PurgeViewController(SsrState *ssr, Settings *settings, ScaleWrapper* scale);

    void tick(U8G2 display) override;

    void viewWasPushed(NavigationController *controller) override;
    void viewWillBePopped(NavigationController *controller) override;

    void render(U8G2 display) override;

    GrindType getGrindType() override;

protected:
    microtime_t target_ms = 0;
};


#endif //GRINDER_PURGEVIEWCONTROLLER_H
