//
// Created by Magnus Nordlander on 2021-03-27.
//

#ifndef FIFTY_FIFTY_GRINDSESSION_H
#define FIFTY_FIFTY_GRINDSESSION_H

#include <types.h>
#include <cstdint>
#include <Model/Settings.h>
#include <vector>

class GrindSession {
public:
    millitime_t startTime;
    millitime_t endTime;
    Settings* settings;
    int32_t tareValue;
    GrindType type;
    unsigned long temporaryTarget;
};


#endif //FIFTY_FIFTY_GRINDSESSION_H
