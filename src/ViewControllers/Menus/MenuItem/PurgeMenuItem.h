//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_PURGEMENUITEM_H
#define GRINDER_PURGEMENUITEM_H

#include "ViewControllerMenuItem.h"
#include <Settings.h>
#include <ViewControllers/Grinding/PurgeViewController.h>

class PurgeMenuItem: public ViewControllerMenuItem {
public:
    explicit PurgeMenuItem(PurgeViewController *viewController, Settings* settings);

    std::string getName() override;

    virtual ~PurgeMenuItem();

private:
    Settings* settings;
};


#endif //GRINDER_PURGEMENUITEM_H
