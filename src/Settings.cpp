//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "Settings.h"

FlashStorage(settingsStorage, SettingsStorageStruct);

unsigned short Settings::getProductivity() const {
    return productivity;
}

void Settings::setProductivity(unsigned short productivity) {
    this->productivity = productivity;
}

unsigned short Settings::getPurgeTargetTime() const {
    return purgeTargetTime;
}

void Settings::setPurgeTargetTime(unsigned short purgeTargetTime) {
    this->purgeTargetTime = purgeTargetTime;
}

unsigned short Settings::getGrindTargetTime() const {
    return grindTargetTime;
}

void Settings::setGrindTargetTime(unsigned short grindTargetTime) {
    this->grindTargetTime = grindTargetTime;
}

unsigned short Settings::getGrindTargetWeight() const {
    return grindTargetWeight;
}

void Settings::setGrindTargetWeight(unsigned short grindTargetWeight) {
    this->grindTargetWeight = grindTargetWeight;
}

float Settings::getScaleCalibration() const {
    return this->scaleCalibration;
}

void Settings::setScaleCalibration(float scaleCalibration) {
    this->scaleCalibration = scaleCalibration;
}

Settings::Settings() {
    this->savedStorage = settingsStorage.read();

    if (!this->savedStorage.valid) {
        this->savedStorage = (SettingsStorageStruct){
                .valid =  false,
                .grindTargetTime = 6400,
                .purgeTargetTime = 1000,
                .grindTargetWeight = 16000,
                .productivity = 2500,
                .scaleCalibration = -1559.11,
                .reactionTime = 450,
        };
    }

    this->productivity = this->savedStorage.productivity;
    this->grindTargetTime = this->savedStorage.grindTargetTime;
    this->purgeTargetTime = this->savedStorage.purgeTargetTime;
    this->grindTargetWeight = this->savedStorage.grindTargetWeight;
    this->scaleCalibration = this->savedStorage.scaleCalibration;
    this->reactionTime = this->savedStorage.reactionTime;
}

void Settings::commitToEEPROM() {
    if (
        this->productivity != this->savedStorage.productivity ||
        this->grindTargetTime != this->savedStorage.grindTargetTime ||
        this->purgeTargetTime != this->savedStorage.purgeTargetTime ||
        this->grindTargetWeight != this->savedStorage.grindTargetWeight ||
        this->scaleCalibration != this->savedStorage.scaleCalibration ||
        this->reactionTime != this->savedStorage.reactionTime
            ) {
        this->savedStorage = (SettingsStorageStruct){
                .valid = true,
                .grindTargetTime = this->grindTargetTime,
                .purgeTargetTime = this->purgeTargetTime,
                .grindTargetWeight = this->grindTargetWeight,
                .productivity = this->productivity,
                .scaleCalibration = this->scaleCalibration,
                .reactionTime = this->reactionTime,
        };

        settingsStorage.write(this->savedStorage);
    }
}

unsigned short Settings::getReactionTime() const {
    return this->reactionTime;
}

void Settings::setReactionTime(unsigned short reactionTime) {
    this->reactionTime = reactionTime;
}
