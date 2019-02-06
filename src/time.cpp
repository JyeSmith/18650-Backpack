#include "time.h"
#include "eeprom.h"

namespace Time {

  uint32_t now = 0;
  uint32_t previousOnTime = 0;
  
  void setup() {

    now = EepromSettings.onTime;
    previousOnTime = EepromSettings.onTime;
    
  }
  
  void update() {

    now = millis() + previousOnTime;
    EepromSettings.onTime = now;
    
  }
  
}


