//
// Created by Magnus Nordlander on 2021-02-08.
//

#include "ScaleWrapper.h"

ScaleWrapper::ScaleWrapper(unsigned short doutPin, unsigned short clkPin, Settings* settings) {
    this->scale.begin(doutPin, clkPin);
    scale.set_scale(settings->getScaleCalibration());

    this->settings = settings;
}

void ScaleWrapper::refresh(unsigned short times) {
    scale.set_scale(settings->getScaleCalibration());
    this->latestValue = scale.get_units(times);
}

void ScaleWrapper::tare(unsigned short times) {
    scale.tare(times);
    this->refresh();
}

float ScaleWrapper::getLatestValue() const {
    return latestValue;
}

void ScaleWrapper::setRefreshing(bool refreshing) {
    this->refreshing = refreshing;
}
