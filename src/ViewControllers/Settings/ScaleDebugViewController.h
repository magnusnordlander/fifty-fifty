//
// Created by Magnus Nordlander on 2021-02-21.
//

#ifndef GRINDER_SCALEDEBUGVIEWCONTROLLER_H
#define GRINDER_SCALEDEBUGVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <ScaleWrapper.h>

class ScaleDebugViewController: public BaseViewController {
public:
    explicit ScaleDebugViewController(ScaleWrapper* scale);

    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;
private:
    ScaleWrapper* scale;
};


#endif //GRINDER_SCALEDEBUGVIEWCONTROLLER_H
