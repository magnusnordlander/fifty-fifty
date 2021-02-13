//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "ScaleWrapper.h"

#define LATEST_VALUE_SIZE 10

ScaleWrapper* ScaleWrapper::singleton_= nullptr;

volatile boolean ScaleWrapper::newDataReady = false;

//interrupt routine:
void ScaleWrapper::dataReadyISR() {
    if (ScaleWrapper::singleton_->scale->update()) {
        ScaleWrapper::newDataReady = true;
    }
}

ScaleWrapper::ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings) {
    this->scale = new HX711_ADC(doutPin, clkPin);
    this->scale->begin();
    this->scale->setCalFactor(settings->getScaleCalibration());
    this->setAccurateMode(false);
    this->scale->start(500);

    this->settings = settings;

    this->latestValues = new std::deque<MeasuringPoint>;

    attachInterrupt(digitalPinToInterrupt(doutPin), dataReadyISR, FALLING);

}

void ScaleWrapper::refresh() {
    scale->setCalFactor(settings->getScaleCalibration());

    if (newDataReady) {
        this->latestValues->push_front((MeasuringPoint) {
            .measuringPoint=this->scale->getData(),
            .microtime=micros(),
        });

        if (this->latestValues->size() > LATEST_VALUE_SIZE) {
            this->latestValues->pop_back();
        }
    }
}

void ScaleWrapper::tare() {
    scale->tare();
}

void ScaleWrapper::tareNoDelay() {
    scale->tareNoDelay();
}

bool ScaleWrapper::getTareStatus() {
    return scale->getTareStatus();
}

void ScaleWrapper::setAccurateMode(bool accurateMode) {
    if (accurateMode) {
        scale->setSamplesInUse(16);
    } else {
        scale->setSamplesInUse(1);
    }

    this->clearAccuracyBuffer();
}

bool ScaleWrapper::accuracyBufferFull() {
    return scale->getDataSetStatus();
}

float ScaleWrapper::getLatestValue() const {
    return scale->getData();
}

float ScaleWrapper::getRateOfChange() {
    if (this->latestValues->size() < 2) {
        return 0.;
    }

    MeasuringPoint first = this->latestValues->back();
    MeasuringPoint last = this->latestValues->front();

    float weightDiff = last.measuringPoint - first.measuringPoint;
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

float ScaleWrapper::measureCalibrationValue(float knownMass) {
    return scale->getNewCalibration(knownMass);
}

void ScaleWrapper::clearAccuracyBuffer() {
    scale->resetSamplesIndex();
}

