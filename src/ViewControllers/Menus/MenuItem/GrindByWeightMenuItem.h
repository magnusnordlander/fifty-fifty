//
// Created by Magnus Nordlander on 2021-02-08.
//

#ifndef GRINDER_GRINDBYWEIGHTMENUITEM_H
#define GRINDER_GRINDBYWEIGHTMENUITEM_H

#include "ViewControllerMenuItem.h"
#include <Model/Settings.h>
#include <ViewControllers/Grinding/GravimetricGrindViewController.h>

class GrindByWeightMenuItem: public ViewControllerMenuItem {
public:
    explicit GrindByWeightMenuItem(GravimetricGrindViewController *viewController, Settings* settings);

    std::string getName() override;

    virtual ~GrindByWeightMenuItem();

private:
    Settings* settings;
};


#endif //GRINDER_GRINDBYWEIGHTMENUITEM_H
