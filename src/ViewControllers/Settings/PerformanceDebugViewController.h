//
// Created by Magnus Nordlander on 2021-02-22.
//

#ifndef GRINDER_PERFORMANCEDEBUGVIEWCONTROLLER_H
#define GRINDER_PERFORMANCEDEBUGVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>

class PerformanceDebugViewController: public BaseViewController {
public:
    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;
};


#endif //GRINDER_PERFORMANCEDEBUGVIEWCONTROLLER_H
