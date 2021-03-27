//
// Created by Magnus Nordlander on 2021-03-28.
//

#ifndef FIFTY_FIFTY_SESSIONSENDER_H
#define FIFTY_FIFTY_SESSIONSENDER_H

#include <types.h>
#include <cstdint>
#include <Model/Settings.h>
#include <vector>
#include "Model/GrindSession.h"

void initSessionSender();
void sendSession(GrindSession gs, std::vector<MeasuringPoint>* measuringPoints);

#endif //FIFTY_FIFTY_SESSIONSENDER_H
