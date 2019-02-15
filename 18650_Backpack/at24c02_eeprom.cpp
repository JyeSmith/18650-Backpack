#include <TinyWireM.h>
#include "at24c02_eeprom.h"
#include "settings.h"
#include "beeper.h"

struct EepromSettingsStruct EepromSettings;
  
void EepromSettingsStruct::setup() {
  
  TinyWireM.begin();
  
}
  
void EepromSettingsStruct::load() {
  
  byte* p = (byte*)(void*)&EepromSettings; // https://playground.arduino.cc/Code/EEPROMWriteAnything
  
  for (uint8_t i = 0; i < sizeof(EepromSettings); i++) {
    TinyWireM.beginTransmission(0x50);
    TinyWireM.write(i);
    TinyWireM.endTransmission();
   
    TinyWireM.requestFrom(0x50,1);
  
    while (!TinyWireM.available()) {}
   
    *p++ = TinyWireM.receive();  
  }  

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

  const byte* p = (const byte*)(const void*)&EepromSettings; // https://playground.arduino.cc/Code/EEPROMWriteAnything
  
  for (uint8_t i = 0; i < sizeof(EepromSettings); i++) {
    TinyWireM.beginTransmission(0x50);
    TinyWireM.write(i);
    TinyWireM.write(*p++);
    TinyWireM.endTransmission();
 
    delay(5); // May not write correctly if a delay is not used.
  }          
}

void EepromSettingsStruct::initDefaults() {
  memcpy_P(this, &EepromDefaults, sizeof(EepromDefaults));
  this->save();
}
