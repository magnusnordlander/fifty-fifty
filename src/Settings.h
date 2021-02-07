//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_SETTINGS_H
#define GRINDER_SETTINGS_H

#include <FlashAsEEPROM.h>

class Settings {
public:
    explicit Settings(EEPROMClass *eeprom);

    unsigned short getProductivity() const;
    void setProductivity(unsigned short productivity);

    unsigned short getPurgeTargetTime() const;
    void setPurgeTargetTime(unsigned short purgeTargetTime);

    unsigned short getGrindTargetTime() const;
    void setGrindTargetTime(unsigned short grindTargetTime);

    unsigned short getGrindTargetWeight() const;
    void setGrindTargetWeight(unsigned short grindTargetWeight);

    void commitToEEPROM();
private:
    unsigned short readUShort(unsigned short addr1, unsigned short addr2, unsigned short sanity, unsigned short fallback);
    void stageUShort(unsigned short addr1, unsigned short addr2, unsigned short value);

    EEPROMClass* eeprom;

    unsigned short productivity; // milligrams per second
    unsigned short purgeTargetTime; // milliseconds
    unsigned short grindTargetTime; // milliseconds
    unsigned short grindTargetWeight; // milligrams

    bool hasChanges = false;
};


#endif //GRINDER_SETTINGS_H
