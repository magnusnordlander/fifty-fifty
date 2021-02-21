//
// Created by Magnus Nordlander on 2021-02-08.
//

#ifndef GRINDER_SCALEWRAPPER_H
#define GRINDER_SCALEWRAPPER_H

#include <deque>
#include <HX711_ADC.h>
#include "Settings.h"
#include <types.h>

class DebugViewController;

typedef struct {
    int32_t measuringPoint;
    microtime_t microtime;
} MeasuringPoint;

class ScaleWrapper {
protected:
    ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings);

    static ScaleWrapper* singleton_;

public:
    static ScaleWrapper *GetInstance(unsigned short doutPin, unsigned short clkPin, Settings* settings);

    void refresh();
    void tare(microtime_t micros = 1000000);

    float measureCalibrationValue(float knownMass, microtime_t relMicros = 100000);

    bool isValueStable(microtime_t relMicros, unsigned short minValues, uint32_t sigma);
    float getLatestValue();
    float getRateOfChange();

    float getReactionCompensatedLatestValue(unsigned short reactionTimeMillis);

    static void dataReadyISR();
private:
    Settings* settings;

    pin_size_t doutPin, clkPin;

    void init() const;
    int32_t readRaw() const;
    float convert(int32_t data) const;

    int32_t averageLast(microtime_t relMicros);
    MeasuringPoint firstValueSince(microtime_t relMicros);
    MeasuringPoint averagePointSince(microtime_t relMicros, unsigned short num);
    MeasuringPoint latestAverage(unsigned short num);

    float scaleStandardDeviation(microtime_t relMicros, unsigned short minValues);

    int32_t tareValue = 0;
    float calibrationValue = 0;

    volatile static microtime_t dataReadAt;
    volatile static int32_t latestData;

    microtime_t latestRefreshed = 0;

    std::deque<MeasuringPoint>* latestValues;

    friend class DebugViewController;
};


#endif //GRINDER_SCALEWRAPPER_H
