//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "ScaleWrapper.h"
#include <cmath>
#include <SimplyAtomic.h>

ScaleWrapper* ScaleWrapper::singleton_= nullptr;

volatile MeasuringPoint allData[LATEST_VALUE_SIZE];
volatile uint16_t head = 0;
volatile bool filledOnce = false;

//interrupt routine:
void ScaleWrapper::dataReadyISR() {
    microtime_t conversionStartTime = micros();
    int32_t data = ScaleWrapper::singleton_->readRaw();

    MeasuringPoint mp = (MeasuringPoint){
        .measuringPoint = data,
        .microtime = conversionStartTime,
    };

    memcpy((void*)&(allData[head]), &mp, sizeof(mp));

    if (!filledOnce && head == LATEST_VALUE_SIZE - 1) {
        filledOnce = true;
    }

    head = (head + 1) % LATEST_VALUE_SIZE;
}

ScaleWrapper::ScaleWrapper(pin_size_t doutPin, pin_size_t clkPin, pin_size_t pdwnPin, Settings* settings) {
    this->pdwnPin = pdwnPin;
    this->doutPin = doutPin;
    this->clkPin = clkPin;

    this->settings = settings;
    this->calibrationValue = settings->getScaleCalibration();
    this->latestValues = new std::deque<MeasuringPoint>;

    this->init();

    attachInterrupt(digitalPinToInterrupt(doutPin), dataReadyISR, FALLING);
}

void ScaleWrapper::refresh() {
    // Grab a copy atomically so that data doesn't change while we're working on it.
    // The interrupt status register will be saved here
    ATOMIC()
    {
        memcpy(safeData, (void*)allData, sizeof(allData));
        safeHead = head;
        safeFilledOnce = filledOnce;
    }
    // The interrupt status register will be restored here

    // Fugly hack while I rewrite this to not use std::deque
    this->latestValues->clear();

    MeasuringPoint prev;
    bool add = false;

    if (!safeFilledOnce) {
        for (unsigned int i = 0; i < safeHead; ++i) {
            if (add) {
                this->latestValues->push_front((MeasuringPoint){
                        .measuringPoint = (prev.measuringPoint + safeData[i].measuringPoint) / 2,
                        .microtime = safeData[i].microtime,
                });
            }

            prev = safeData[i];
            add = true;
        }
    } else {
        uint16_t i = safeHead;
        do {
            if (add) {
                this->latestValues->push_front((MeasuringPoint){
                        .measuringPoint = (prev.measuringPoint + safeData[i].measuringPoint) / 2,
                        .microtime = safeData[i].microtime,
                });
            }

            prev = safeData[i];
            add = true;
            i = (i + 1) % LATEST_VALUE_SIZE;
        } while (i != safeHead);
    }

    latestRefreshed = this->latestValues->front().microtime;

    if (this->tareValue == 0 && this->isValueStableHighAccuracy()) {
        this->tare(1000000);
    }
}

void ScaleWrapper::tare(microtime_t rel_micros) {
    this->tareValue = averageLast(rel_micros);
}

float ScaleWrapper::getLatestValue() {
    return this->convert(this->latestAverage(SPEED/10).measuringPoint);
}

float ScaleWrapper::getLatestValue(microtime_t relMicros) {
    return this->convert(this->averageLast(relMicros));
}

float ScaleWrapper::getRateOfChange() {
    if (this->latestValues->size() < 2) {
        return 0.;
    }

    MeasuringPoint first = this->averagePointSince(1000000, 10);
    MeasuringPoint last = this->latestAverage(10);

    microtime_t diff = last.microtime - first.microtime;

    float weightDiff = this->convert(last.measuringPoint) - this->convert(first.measuringPoint);
    auto timeDiff = (float)((double)diff / 1000000.);

    return weightDiff / timeDiff;
}

float ScaleWrapper::getReactionCompensatedLatestValue(unsigned short reactionTimeMillis) {
    float rateOfChange = this->getRateOfChange();
    float latestValue = this->getLatestValue();

    if (rateOfChange < 0.01) {
        return latestValue;
    }

    float reactionTimeSeconds = (float)reactionTimeMillis / 1000;

    return latestValue + rateOfChange*reactionTimeSeconds;
}

ScaleWrapper *ScaleWrapper::GetInstance(pin_size_t doutPin, pin_size_t clkPin, pin_size_t pdwnPin, Settings *settings) {
    if(singleton_==nullptr){
        singleton_ = new ScaleWrapper(doutPin, clkPin, pdwnPin, settings);
    }
    return singleton_;
}

float ScaleWrapper::measureCalibrationValue(float knownMass, microtime_t relMicros) {
    int32_t avg = this->averageLast(relMicros);

    this->calibrationValue = (float)(avg - tareValue) / knownMass;

    return this->calibrationValue;
}

void ScaleWrapper::init() const {
    pinMode(this->pdwnPin, OUTPUT);
    pinMode(this->clkPin, OUTPUT);
    pinMode(this->doutPin, INPUT);

    digitalWrite(this->pdwnPin, LOW);

    delay(1);

    digitalWrite(this->pdwnPin, HIGH);
}

int32_t ScaleWrapper::readRaw() const {
    pin_size_t clk = ScaleWrapper::singleton_->clkPin;
    pin_size_t dout = ScaleWrapper::singleton_->doutPin;

    int32_t data = 0;

    // Read 24 bits
    for(int i=23 ; i >= 0; i--) {
        digitalWrite(clk, HIGH);
        data = (data << 1) + digitalRead(dout);
        digitalWrite(clk, LOW);
    }

    /* Bit 23 is acutally the sign bit. Shift by 8 to get it to the
     * right position (31), divide by 256 to restore the correct value.
     */
    data = (data << 8) / 256;

    /* The data pin now is high or low depending on the last bit that
     * was read.
     * To get it to the default state (high) we toggle the clock one
     * more time (see datasheet).
     */
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);

    return data;
}

float ScaleWrapper::convert(int32_t data) const {
    return (float)(data - tareValue) / calibrationValue;
}

int32_t ScaleWrapper::averageLast(microtime_t relMicros) {
    long s = latestValues->size();
    long sum = 0;
    uint8_t valuesUsed = 0;
    microtime_t current = micros();

    for (int i = 0; i < s; i++) {
        MeasuringPoint p = latestValues->at(i);
        if (current - p.microtime <= relMicros) {
            sum += p.measuringPoint;
            valuesUsed++;
        }
    }

    if (valuesUsed == 0) {
        return 0;
    }

    return sum / valuesUsed;
}

bool ScaleWrapper::isValueStableHighAccuracy() {
    return this->isValueStable(2000000, 5, 250);
}

bool ScaleWrapper::isValueStableLowAccuracy() {
    return this->isValueStable(500000, 5, 1000);
}

bool ScaleWrapper::isValueStable(microtime_t relMicros, unsigned short minValues, uint32_t sigma) {
    float val = this->scaleStandardDeviation(relMicros, minValues);

    return val < sigma;
}



float ScaleWrapper::scaleStandardDeviation(microtime_t relMicros, unsigned short minValues) {
    long s = latestValues->size();
    long sum = 0;
    uint8_t valuesUsed = 0;
    microtime_t current = micros();

    for (int i = 0; i < s; i++) {
        MeasuringPoint p = latestValues->at(i);
        if (current - p.microtime <= relMicros) {
            sum += p.measuringPoint;
            valuesUsed++;
        }
    }

    if (valuesUsed < minValues || valuesUsed == 0) {
        return NAN;
    }

    int32_t mean = sum / valuesUsed;
    float sd = 0;

    for (int i = 0; i < s; i++) {
        MeasuringPoint p = latestValues->at(i);
        if (current - p.microtime <= relMicros) {
            sd += pow(p.measuringPoint - mean, 2);
        }
    }

    return sqrt(sd/(float)valuesUsed);
}

MeasuringPoint ScaleWrapper::firstValueSince(microtime_t relMicros) {
    microtime_t current = micros();

    for (unsigned int i = latestValues->size() - 1; i >= 0; i--) {
        MeasuringPoint p = latestValues->at(i);
        if (current - p.microtime <= relMicros) {
            return p;
        }
    }

    return latestValues->back();
}

MeasuringPoint ScaleWrapper::averagePointSince(microtime_t relMicros, unsigned short num) {
    microtime_t current = micros();

    int32_t sum = 0;
    unsigned short foundNum = 0;
    microtime_t lastTime = 0;

    for (unsigned int i = latestValues->size() - 1; i >= 0; i--) {
        MeasuringPoint p = latestValues->at(i);
        if (current - p.microtime <= relMicros) {
            foundNum++;
            sum += p.measuringPoint;
            lastTime = p.microtime;

            if (foundNum >= num) {
                break;
            }
        }
    }

    if (foundNum == 0) {
        return latestValues->back();
    }

    return MeasuringPoint{.measuringPoint=sum/foundNum, .microtime=lastTime};
}

MeasuringPoint ScaleWrapper::latestAverage(unsigned short num) {
    int32_t sum = 0;
    unsigned short foundNum = 0;
    microtime_t lastTime = 0;

    for (unsigned int i = 0; i < num; i++) {
        if (i < latestValues->size()) {
            MeasuringPoint p = latestValues->at(i);
            foundNum++;
            sum += p.measuringPoint;
            lastTime = p.microtime;
        }
    }

    if (foundNum == 0) {
        return latestValues->front();
    }

    return MeasuringPoint{.measuringPoint=sum/foundNum, .microtime=lastTime};
}

microtime_t ScaleWrapper::bufSize() {
    return this->latestValues->front().microtime - this->latestValues->back().microtime;
}

MeasuringPoint ScaleWrapper::min() {
    MeasuringPoint val = (MeasuringPoint){
        .measuringPoint = 99999999,
        .microtime = 0
    };

    for (unsigned int i = 0; i < latestValues->size(); i++) {
        MeasuringPoint p = latestValues->at(i);
        if (p.measuringPoint < val.measuringPoint) {
            val = p;
        }
    }

    return val;
}

MeasuringPoint ScaleWrapper::max() {
    MeasuringPoint val = (MeasuringPoint){
            .measuringPoint = 0,
            .microtime = 0
    };

    for (unsigned int i = 0; i < latestValues->size(); i++) {
        MeasuringPoint p = latestValues->at(i);
        if (p.measuringPoint > val.measuringPoint) {
            val = p;
        }
    }

    return val;
}