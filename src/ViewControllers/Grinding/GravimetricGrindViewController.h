//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_GRAVIMETRICGRINDVIEWCONTROLLER_H
#define GRINDER_GRAVIMETRICGRINDVIEWCONTROLLER_H

#include "BaseGrindViewController.h"
#include <Settings.h>
#include <ScaleWrapper.h>
#include <View/ProgressBarView.h>

class GravimetricGrindViewController: public BaseGrindViewController {
public:
    GravimetricGrindViewController(SsrState *ssr, ScaleWrapper *scale,
                                   Settings *settings);

    void tick(U8G2 display) override;

    void viewWasPushed(NavigationController *controller) override;

    void viewWillBePopped(NavigationController *controller) override;

    void render(U8G2 display) override;

    virtual ~GravimetricGrindViewController();

private:
    void renderGrindingView(U8G2 display);
    void renderTaringView(U8G2 display);

    void startTare();

    Settings* settings;
    ScaleWrapper* scale;
    ProgressBarView* progressBar;

    bool taring = false;

    unsigned long target_mg = 0;
    unsigned short reaction_time = 0;
};


#endif //GRINDER_GRAVIMETRICGRINDVIEWCONTROLLER_H
