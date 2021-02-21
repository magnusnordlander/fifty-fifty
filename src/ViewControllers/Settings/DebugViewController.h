//
// Created by Magnus Nordlander on 2021-02-21.
//

#ifndef GRINDER_DEBUGVIEWCONTROLLER_H
#define GRINDER_DEBUGVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <ScaleWrapper.h>

class DebugViewController: public BaseViewController {
public:
    explicit DebugViewController(ScaleWrapper* scale);

    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;
private:
    ScaleWrapper* scale;
};


#endif //GRINDER_DEBUGVIEWCONTROLLER_H
