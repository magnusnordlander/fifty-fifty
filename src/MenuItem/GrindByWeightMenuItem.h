//
// Created by Magnus Nordlander on 2021-02-08.
//

#ifndef GRINDER_GRINDBYWEIGHTMENUITEM_H
#define GRINDER_GRINDBYWEIGHTMENUITEM_H

#include "ViewControllerMenuItem.h"
#include <Settings.h>

class GrindByWeightMenuItem: public ViewControllerMenuItem {
public:
    explicit GrindByWeightMenuItem(BaseViewController *viewController, Settings* settings);

    std::string getName() override;

private:
    Settings* settings;
};


#endif //GRINDER_GRINDBYWEIGHTMENUITEM_H
