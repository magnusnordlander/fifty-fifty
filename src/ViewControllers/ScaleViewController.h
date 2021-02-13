//
// Created by Magnus Nordlander on 2021-02-13.
//

#ifndef GRINDER_SCALEVIEWCONTROLLER_H
#define GRINDER_SCALEVIEWCONTROLLER_H


#include "BaseViewController.h"
#include <ScaleWrapper.h>

class ScaleViewController: public BaseViewController {
public:
    explicit ScaleViewController(ScaleWrapper *scale);

    void render(U8G2 display) override;

    void handleButtonState(bool state) override;

protected:
    ScaleWrapper* scale;
};



#endif //GRINDER_SCALEVIEWCONTROLLER_H
