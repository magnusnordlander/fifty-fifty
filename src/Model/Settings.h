//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_SETTINGS_H
#define GRINDER_SETTINGS_H

#include <FlashAsEEPROM.h>

typedef struct {
    bool valid;
    unsigned short grindTargetTime;
    unsigned short purgeTargetTime;
    unsigned short grindTargetWeight;
    unsigned short productivity;
    float scaleCalibration;
    unsigned short reactionTime;
} SettingsStorageStruct;

class Settings {
public:
    explicit Settings();

    unsigned short getProductivity() const;
    void setProductivity(unsigned short productivity);

    unsigned short getPurgeTargetTime() const;
    void setPurgeTargetTime(unsigned short purgeTargetTime);

    unsigned short getGrindTargetTime() const;
    void setGrindTargetTime(unsigned short grindTargetTime);

    unsigned short getGrindTargetWeight() const;
    void setGrindTargetWeight(unsigned short grindTargetWeight);

    float getScaleCalibration() const;
    void setScaleCalibration(float scaleCalibration);

    unsigned short getReactionTime() const;
    void setReactionTime(unsigned short reactionTime);

    void commitToEEPROM();
private:
    unsigned short productivity; // milligrams per second
    unsigned short purgeTargetTime; // milliseconds
    unsigned short grindTargetTime; // milliseconds
    unsigned short grindTargetWeight; // milligrams
    float scaleCalibration; // unitless
    unsigned short reactionTime; // milliseconds

    SettingsStorageStruct savedStorage;
};


#endif //GRINDER_SETTINGS_H
