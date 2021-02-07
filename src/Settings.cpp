//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "Settings.h"

//*************************************************************************
//        EEPROM setting emulation
//  Grind target time: EEPROM @ Pos. MSB->100 & LSB->101
//  Purge target time: EEPROM @ Pos. MSB->102 & LSB->103
//  Performance: EEPROM @ Pos. MSB->104 & LSB->105
//*************************************************************************

/* void validateEEPROMData() {
    if (Purge_Target_Time > 10000) {
        Purge_Target_Time = 1000;
    }

    if (Grind_Target_Time > 20000) {
        Grind_Target_Time = 6400;
    }

    if (Productivity > 16000) {
        Productivity = 2500;
    }
}
*/

unsigned short Settings::getProductivity() const {
    return productivity;
}

void Settings::setProductivity(unsigned short productivity) {
    if (this->productivity != productivity) {
        this->productivity = productivity;
        this->stageUShort(104, 105, productivity);
    }
}

unsigned short Settings::getPurgeTargetTime() const {
    return purgeTargetTime;
}

void Settings::setPurgeTargetTime(unsigned short purgeTargetTime) {
    if (this->purgeTargetTime != purgeTargetTime) {
        this->purgeTargetTime = purgeTargetTime;
        this->stageUShort(102, 103, purgeTargetTime);
    }
}

unsigned short Settings::getGrindTargetTime() const {
    return grindTargetTime;
}

void Settings::setGrindTargetTime(unsigned short grindTargetTime) {
    if (this->grindTargetTime != grindTargetTime) {
        this->grindTargetTime = grindTargetTime;
        this->stageUShort(100, 101, grindTargetTime);
    }
}

unsigned short Settings::getGrindTargetWeight() const {
    return grindTargetWeight;
}

void Settings::setGrindTargetWeight(unsigned short grindTargetWeight) {
    if (this->grindTargetWeight != grindTargetWeight) {
        this->grindTargetWeight = grindTargetWeight;
        this->stageUShort(106, 107, grindTargetWeight);
    }
}

Settings::Settings(EEPROMClass *eeprom) : eeprom(eeprom) {
    if (eeprom->isValid()) {
        this->productivity = this->readUShort(104, 105, 16000, 2500);
        this->grindTargetTime = this->readUShort(100, 101, 20000, 6400);
        this->purgeTargetTime = this->readUShort(102, 103, 10000, 1000);
        this->grindTargetWeight = this->readUShort(106, 107, 50000, 16000);
    } else {
        this->productivity = 2500;
        this->grindTargetTime = 6400;
        this->purgeTargetTime = 1000;
        this->grindTargetWeight = 16000;
    }
}

unsigned short Settings::readUShort(unsigned short addr1, unsigned short addr2, unsigned short sanity, unsigned short fallback)
{
    byte highByte = this->eeprom->read(addr1);
    byte lowByte = this->eeprom->read(addr2);
    unsigned short value = lowByte + (highByte*255);

    if (value > sanity) {
        return fallback;
    }

    return value;
}

void Settings::stageUShort(unsigned short addr1, unsigned short addr2, unsigned short value) {
    byte highByte = value/255;
    byte lowByte =  value - (highByte*255);
    this->eeprom->write(addr1, highByte);
    this->eeprom->write(addr2, lowByte);
}

void Settings::commitToEEPROM() {
    this->eeprom->commit();
}


