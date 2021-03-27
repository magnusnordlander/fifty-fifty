//
// Created by Magnus Nordlander on 2021-02-13.
//

#ifndef GRINDER_CALIBRATIONVIEWCONTROLLER_H
#define GRINDER_CALIBRATIONVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Model/Settings.h>
#include <ScaleWrapper.h>
#include <View/ProgressBarView.h>

#define STATE_PRE_TARE 0
#define STATE_TARING 1
#define STATE_TARED 2
#define STATE_MEASURING 3

class CalibrationViewController: public BaseViewController {
public:
    explicit CalibrationViewController(Settings* settings, ScaleWrapper* scale);
    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;

    void viewWillBePushed(NavigationController *controller) override;

    void viewWasPopped(NavigationController *controller) override;

    void tick(U8G2 display) override;

    virtual ~CalibrationViewController();

protected:
    void renderPreTareView(U8G2 display);
    void renderTaringView(U8G2 display);
    void renderTaredView(U8G2 display);
    void renderMeasuringView(U8G2 display);

    Settings* settings;
    ScaleWrapper* scale;

    ProgressBarView* progressBar;

    unsigned short state = STATE_PRE_TARE;
};


#endif //GRINDER_CALIBRATIONVIEWCONTROLLER_H
