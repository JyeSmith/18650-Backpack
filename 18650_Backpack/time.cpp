#include "time.h"
#include "at24c02_eeprom.h"

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
