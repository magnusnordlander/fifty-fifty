//
// Created by Magnus Nordlander on 2021-02-07.
//

#ifndef GRINDER_POPNAVIGATIONANDCOMMITEEPROMMENUITEM_H
#define GRINDER_POPNAVIGATIONANDCOMMITEEPROMMENUITEM_H

#include "PopNavigationMenuItem.h"
#include <Model/Settings.h>

class PopNavigationAndCommitEEPROMMenuItem: public PopNavigationMenuItem {
public:
    explicit PopNavigationAndCommitEEPROMMenuItem(const std::string& name, Settings* settings);

    void activate(NavigationController *controller) override;
private:
    Settings* settings;
};


#endif //GRINDER_POPNAVIGATIONANDCOMMITEEPROMMENUITEM_H
