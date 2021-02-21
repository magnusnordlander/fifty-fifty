//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "ScaleWrapper.h"
#include <cmath>

#define LATEST_VALUE_SIZE 50

ScaleWrapper* ScaleWrapper::singleton_= nullptr;

volatile microtime_t ScaleWrapper::dataReadAt = 0;
volatile int32_t ScaleWrapper::latestData = 0;

//interrupt routine:
void ScaleWrapper::dataReadyISR() {
    microtime_t conversionStartTime = micros();
    int32_t data = ScaleWrapper::singleton_->readRaw();

    ScaleWrapper::dataReadAt = conversionStartTime;
    ScaleWrapper::latestData = data;
}

ScaleWrapper::ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings) {
    this->doutPin = doutPin;
    this->clkPin = clkPin;

    this->init();

    this->settings = settings;
    this->calibrationValue = settings->getScaleCalibration();
    this->latestValues = new std::deque<MeasuringPoint>;

    attachInterrupt(digitalPinToInterrupt(doutPin), dataReadyISR, FALLING);

}

void ScaleWrapper::refresh() {
    // Grab a copy immediately so that data doesn't change while we're working on it.
    microtime_t lastAdded = ScaleWrapper::dataReadAt;
    int32_t d = ScaleWrapper::latestData;

    if (latestRefreshed < lastAdded) {
        this->latestValues->push_front((MeasuringPoint) {
            .measuringPoint=d,
            .microtime=lastAdded,
        });

        if (this->latestValues->size() > LATEST_VALUE_SIZE) {
            this->latestValues->pop_back();
        }

        latestRefreshed = lastAdded;

        if (this->tareValue == 0 && this->isValueStable(1000000, 5, 200)) {
            this->tare(1000000);
        }
    }
}

void ScaleWrapper::tare(microtime_t rel_micros) {
    this->tareValue = averageLast(rel_micros);
}

float ScaleWrapper::getLatestValue() {
    return this->convert(this->latestValues->front().measuringPoint);
}

float ScaleWrapper::getRateOfChange() {
    if (this->latestValues->size() < 2) {
        return 0.;
    }

    MeasuringPoint first = this->firstValueSince(1000000);
    MeasuringPoint last = this->latestValues->front();

    float weightDiff = this->convert(last.measuringPoint) - this->convert(first.measuringPoint);
    auto timeDiff = (float)((double)(last.microtime - first.microtime) / 1000000.);

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

ScaleWrapper *ScaleWrapper::GetInstance(unsigned short doutPin, unsigned short clkPin, Settings *settings) {
    if(singleton_==nullptr){
        singleton_ = new ScaleWrapper(doutPin, clkPin, settings);
    }
    return singleton_;
}

float ScaleWrapper::measureCalibrationValue(float knownMass, microtime_t relMicros) {
    int32_t avg = this->averageLast(relMicros);

    this->calibrationValue = (float)(avg - tareValue) / knownMass;

    return this->calibrationValue;
}

void ScaleWrapper::init() const {
    pinMode(this->clkPin, OUTPUT);
    pinMode(this->doutPin, INPUT);

    digitalWrite(this->clkPin, LOW);
}

int32_t ScaleWrapper::readRaw() const {
    uint8_t sckPin = this->clkPin;
    uint8_t doutPin = this->doutPin;

    // Gain is 128, which means read one extra bit
    uint8_t gain = 1;

    int32_t data = 0;
    uint8_t dout;

    for (uint8_t i = 0; i < (24 + gain); i++)
    { //read 24 bit data + set gain and start next conversion
        digitalWrite(sckPin, HIGH);
        digitalWrite(sckPin, LOW);
        if (i < (24))
        {
            dout = digitalRead(doutPin);
            data = (data << 1) | dout;
        }
    }

    /*
    The HX711 output range is min. 0x800000 and max. 0x7FFFFF (the value rolls over).
    In order to convert the range to min. 0x000000 and max. 0xFFFFFF,
    the 24th bit must be changed from 0 to 1 or from 1 to 0.
    */
    data = data ^ 0x800000; // flip the 24th bit

    if (data > 0xFFFFFF)
    {
        //Serial.println("dataOutOfRange");
    }

    return data;
}

float ScaleWrapper::convert(int32_t data) const {
    return (float)(data - tareValue) / calibrationValue;
}

int32_t ScaleWrapper::averageLast(microtime_t relMicros) {
    long s = latestValues->size();
    long sum = 0;
    uint8_t valuesUsed = 0;
    microtime_t threshold = micros() - relMicros;

    for (int i = 0; i < s; i++) {
        MeasuringPoint p = latestValues->at(i);
        if (p.microtime > threshold) {
            sum += p.measuringPoint;
            valuesUsed++;
        }
    }

    if (valuesUsed == 0) {
        return 0;
    }

    return sum / valuesUsed;
}

bool ScaleWrapper::isValueStable(microtime_t relMicros, unsigned short minValues, uint32_t sigma) {
    long s = latestValues->size();
    long sum = 0;
    uint8_t valuesUsed = 0;
    microtime_t threshold = micros() - relMicros;

    for (int i = 0; i < s; i++) {
        MeasuringPoint p = latestValues->at(i);
        if (p.microtime > threshold) {
            sum += p.measuringPoint;
            valuesUsed++;
        }
    }

    if (valuesUsed < minValues || valuesUsed == 0) {
        return false;
    }

    int32_t mean = sum / valuesUsed;
    float sd = 0;

    for (int i = 0; i < s; i++) {
        MeasuringPoint p = latestValues->at(i);
        if (p.microtime > threshold) {
            sd += pow(p.measuringPoint - mean, 2);
        }
    }

    float val = sqrt(sd/(float)valuesUsed);

    return val < sigma;
}

MeasuringPoint ScaleWrapper::firstValueSince(microtime_t relMicros) {
    microtime_t threshold = micros() - relMicros;

    for (unsigned int i = latestValues->size() - 1; i >= 0; i--) {
        MeasuringPoint p = latestValues->at(i);
        if (p.microtime > threshold) {
            return p;
        }
    }

    return latestValues->back();
}

