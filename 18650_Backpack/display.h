#ifndef DISPLAY_H
#define DISPLAY_H

#include "settings.h"
#include "voltage.h"
#include "Time.h"

namespace Display {

  enum displayStatEnum{
    homeScreen = 0,
    batteryAlarmScreen = 1,
    callSignScreenChar = 2,
    maxEnum = 3 // must be last in list
  };
  extern displayStatEnum displayState;
  extern uint8_t callSignLetterSelected;
  
  void setup();
  void update();
  void drawHomeScreen();
  void drawBatteryAlarmScreen();
  void drawCallSignScreenChar();
  void drawScreenNumber();
  void drawBattery(uint8_t percentage);
  void clear();
  void switchFrame();
  
}

#endif


