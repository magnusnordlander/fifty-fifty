//
// Created by Magnus Nordlander on 2021-02-08.
//

#ifndef GRINDER_SCALEWRAPPER_H
#define GRINDER_SCALEWRAPPER_H

#include <HX711.h>
#include "Settings.h"

class ScaleWrapper {
public:
    explicit ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings);

    void refresh(unsigned short times = 1);
    void tare(unsigned short times = 10);

    void setRefreshing(bool refreshing);

    float getLatestValue() const;

private:
    float latestValue = 0;

    Settings* settings;
    HX711 scale;

    bool refreshing = false;
};


#endif //GRINDER_SCALEWRAPPER_H
