//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "ScaleWrapper.h"

#define LATEST_VALUE_SIZE 10

ScaleWrapper::ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings) {
    this->scale.begin(doutPin, clkPin);
    scale.set_scale(settings->getScaleCalibration());

    this->settings = settings;

    this->latestValues = new std::deque<MeasuringPoint>();
}

void ScaleWrapper::refresh(unsigned short times) {
    if (this->refreshing) {
        scale.set_scale(settings->getScaleCalibration());
        this->latestValue = scale.get_units(times);

        this->latestValues->push_front((MeasuringPoint) {
            .measuringPoint=this->latestValue,
            .microtime=micros()
        });

        if (this->latestValues->size() > LATEST_VALUE_SIZE) {
            this->latestValues->pop_back();
        }
    }
}

void ScaleWrapper::tare(unsigned short times) {
    scale.tare(times);
    this->refresh();
}

float ScaleWrapper::getLatestValue() const {
    return latestValue;
}

void ScaleWrapper::setRefreshing(bool refreshing) {
    if (!refreshing) {
        this->latestValues->clear();
    }

    this->refreshing = refreshing;
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

float ScaleWrapper::getReactionCompensatedLatestValue(unsigned long reactionTimeMicros) {
    float rateOfChange = this->getRateOfChange();

    if (rateOfChange < 0.01) {
        return this->latestValue;
    }

    float reactionTimeSeconds = (float)reactionTimeMicros / 1000000;

    return this->latestValue + rateOfChange*reactionTimeSeconds;
}

