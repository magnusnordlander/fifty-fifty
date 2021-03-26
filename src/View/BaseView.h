//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_BASEVIEW_H
#define GRINDER_BASEVIEW_H

#include <U8g2lib.h>

class BaseView {
public:
    virtual void drawRelative(U8G2 display, unsigned short x, unsigned short y);

    virtual ~BaseView() = default;
};


#endif //GRINDER_BASEVIEW_H
