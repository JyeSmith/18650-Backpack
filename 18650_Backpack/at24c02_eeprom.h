#ifndef AT24C02_EEPROM_H
#define AT24C02_EEPROM_H

#include <Arduino.h>
#include "settings.h"
  
struct EepromSettingsStruct {
  uint16_t versionNumber;
  char callSign[13];
  uint16_t alarmVoltage;
  float mAh;
  uint32_t onTime;
  
  void load();
  void save();
  void initDefaults();
};

PROGMEM const struct {
  uint16_t versionNumber = eepromVersionNumber;
  char callSign[13] = "CALLSIGNHERE";
  uint16_t alarmVoltage = 310;
  float mAh = 0;
  uint32_t onTime = 0;
} EepromDefaults;

extern EepromSettingsStruct EepromSettings;

#endif
