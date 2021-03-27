//
// Created by Magnus Nordlander on 2021-03-28.
//

#ifndef FIFTY_FIFTY_WIFIDEBUGVIEWCONTROLLER_H
#define FIFTY_FIFTY_WIFIDEBUGVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>

class WifiDebugViewController: public BaseViewController {
public:
    void render(U8G2 display) override;

    void handleButtonEvent(ButtonEvent event) override;
};

#endif //FIFTY_FIFTY_WIFIDEBUGVIEWCONTROLLER_H
