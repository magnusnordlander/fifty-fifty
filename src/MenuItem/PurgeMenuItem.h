//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_PURGEMENUITEM_H
#define GRINDER_PURGEMENUITEM_H

#include "ViewControllerMenuItem.h"
#include <Settings.h>

class PurgeMenuItem: public ViewControllerMenuItem {
public:
    explicit PurgeMenuItem(BaseViewController *viewController, Settings* settings);

    std::string getName() override;

private:
    Settings* settings;
};


#endif //GRINDER_PURGEMENUITEM_H
