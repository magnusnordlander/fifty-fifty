//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_BASEGRINDVIEWCONTROLLER_H
#define GRINDER_BASEGRINDVIEWCONTROLLER_H

#include "ViewControllers/BaseViewController.h"
#include <SsrState.h>
#include <Model/Settings.h>
#include <ScaleWrapper.h>
#include <types.h>
#include <vector>
#include "Model/GrindSession.h"

class BaseGrindViewController: public BaseViewController {
public:
    explicit BaseGrindViewController(SsrState *ssr, Settings* settings, ScaleWrapper* scale);

    void render(U8G2 display) override;

    void tick(U8G2 display) override;

    void viewWasPushed(NavigationController *controller) override;

    void viewWillBePopped(NavigationController *controller) override;

    void subviewWillBePushed(NavigationController *controller, BaseViewController *) override;

    void setTemporaryTarget(millitime_t target);

    virtual GrindType getGrindType();

    static void initShared();

protected:
    Settings* settings;
    ScaleWrapper* scale;
    SsrState* ssr;
    millitime_t startTime;
    millitime_t stopTime;
    millitime_t elapsedMillis() const;
    unsigned long temporary_target = 0;
    bool grinding = false;
    millitime_t lastMP = 0;
};


#endif //GRINDER_BASEGRINDVIEWCONTROLLER_H
