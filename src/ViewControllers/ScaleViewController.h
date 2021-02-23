//
// Created by Magnus Nordlander on 2021-02-13.
//

#ifndef GRINDER_SCALEVIEWCONTROLLER_H
#define GRINDER_SCALEVIEWCONTROLLER_H


#include "BaseViewController.h"
#include <ScaleWrapper.h>
#include <View/ProgressBarView.h>

class ScaleViewController: public BaseViewController {
public:
    explicit ScaleViewController(ScaleWrapper *scale);

    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;

    void tick(U8G2 display) override;

    virtual ~ScaleViewController();

protected:
    ScaleWrapper* scale;

    boolean taring = false;
    float displayValue = 0.;
    uint8_t tickCounter = 0;

    ProgressBarView* progressBar;
};



#endif //GRINDER_SCALEVIEWCONTROLLER_H
