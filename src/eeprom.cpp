#include "eeprom.h"
#include "settings.h"
#include <EEPROM.h>

#include "settings.h"

struct EepromSettingsStruct EepromSettings;

void EepromSettingsStruct::load() {
  EEPROM.get(0, *this);

  // If a button is held during boot then zero time and mAh
  if ( !digitalRead(buttonMode) || !digitalRead(buttonChange) ) {
    EepromSettings.onTime = 0;
    EepromSettings.mAh = 0;
  }

  if (this->versionNumber != eepromVersionNumber) {
    this->initDefaults();
  }
}

void EepromSettingsStruct::save() {
//  this->alarmVoltageCritical = this->alarmVoltage - 10;
  EEPROM.put(0, *this);
}

void EepromSettingsStruct::initDefaults() {
  memcpy_P(this, &EepromDefaults, sizeof(EepromDefaults));
  this->save();
}
