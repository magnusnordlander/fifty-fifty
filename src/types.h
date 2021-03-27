//
// Created by Magnus Nordlander on 2021-02-21.
//

#ifndef GRINDER_TYPES_H
#define GRINDER_TYPES_H

#include <cstdint>

typedef unsigned long microtime_t;
typedef unsigned long millitime_t;
typedef struct {
    microtime_t external;
    microtime_t manual;
    microtime_t rotation;
    microtime_t button;
    microtime_t tick;
    microtime_t loop;
} TimingStruct;

typedef struct {
    int32_t measuringPoint;
    microtime_t microtime;
} MeasuringPoint;

enum GrindType { manual, purge, grindByTime, grindByWeight };

#endif //GRINDER_TYPES_H
