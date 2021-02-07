//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_GRINDMENUITEM_H
#define GRINDER_GRINDMENUITEM_H

#include "ViewControllerMenuItem.h"
#include <Settings.h>

class GrindMenuItem: public ViewControllerMenuItem {
public:
    explicit GrindMenuItem(BaseViewController *viewController, Settings* settings);

    std::string getName() override;

private:
    Settings* settings;
};


#endif //GRINDER_GRINDMENUITEM_H
