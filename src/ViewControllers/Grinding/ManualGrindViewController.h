//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_MANUALGRINDVIEWCONTROLLER_H
#define GRINDER_MANUALGRINDVIEWCONTROLLER_H

#include "BaseGrindViewController.h"
#include "SsrState.h"
#include <types.h>

class ManualGrindViewController: public BaseGrindViewController {
public:
    using BaseGrindViewController::BaseGrindViewController;

    void render(U8G2 display) override;
};


#endif //GRINDER_MANUALGRINDVIEWCONTROLLER_H
