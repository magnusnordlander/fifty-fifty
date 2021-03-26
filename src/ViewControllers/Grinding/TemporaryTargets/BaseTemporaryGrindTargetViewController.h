//
// Created by Magnus Nordlander on 2021-02-14.
//

#ifndef GRINDER_BASETEMPORARYGRINDTARGETVIEWCONTROLLER_H
#define GRINDER_BASETEMPORARYGRINDTARGETVIEWCONTROLLER_H

#include <ViewControllers/BaseViewController.h>
#include <Settings.h>
#include <ViewControllers/Grinding/PurgeViewController.h>


class BaseTemporaryGrindTargetViewController: public BaseViewController {
public:
    explicit BaseTemporaryGrindTargetViewController(Settings *settings);

    void handleRotation(int encoderDiff) override;

protected:
    unsigned short target = 0;
    unsigned short settingSensitivity = 16;
    Settings* settings;
};


#endif //GRINDER_BASETEMPORARYGRINDTARGETVIEWCONTROLLER_H
