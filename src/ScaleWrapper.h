//
// Created by Magnus Nordlander on 2021-02-08.
//

#ifndef GRINDER_SCALEWRAPPER_H
#define GRINDER_SCALEWRAPPER_H

#include <deque>
#include <HX711_ADC.h>
#include "Settings.h"

typedef struct {
    float measuringPoint;
    unsigned long microtime;
} MeasuringPoint;

class ScaleWrapper {
protected:
    ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings);

    static ScaleWrapper* singleton_;

public:
    static ScaleWrapper *GetInstance(unsigned short doutPin, unsigned short clkPin, Settings* settings);

    void refresh();
    void tare();
    void tareNoDelay();
    bool getTareStatus();

    void setAccurateMode(bool accurateMode);
    bool accuracyBufferFull();
    void clearAccuracyBuffer();
    float measureCalibrationValue(float knownMass);

    float getLatestValue() const;
    float getRateOfChange();

    float getReactionCompensatedLatestValue(unsigned short reactionTimeMillis);

    static void dataReadyISR();
private:
    Settings* settings;
    HX711_ADC* scale;

    volatile static boolean newDataReady;

    std::deque<MeasuringPoint>* latestValues;
};


#endif //GRINDER_SCALEWRAPPER_H
