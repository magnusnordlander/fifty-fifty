//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_PROGRESSBARVIEW_H
#define GRINDER_PROGRESSBARVIEW_H

#include "BaseView.h"

class ProgressBarView: public BaseView {
public:
    void drawRelative(U8G2 display, unsigned short x, unsigned short y) override;
};

#endif //GRINDER_PROGRESSBARVIEW_H
