//
// Created by Magnus Nordlander on 2021-02-13.
//

#ifndef GRINDER_CALIBRATIONVIEWCONTROLLER_H
#define GRINDER_CALIBRATIONVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Settings.h>
#include <ScaleWrapper.h>

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

protected:
    Settings* settings;
    ScaleWrapper* scale;

    unsigned short state = STATE_PRE_TARE;
};


#endif //GRINDER_CALIBRATIONVIEWCONTROLLER_H
