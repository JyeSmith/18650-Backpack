#ifndef TIME_H
#define TIME_H

#include <Arduino.h>

namespace Time {

  extern uint32_t now;
  extern uint32_t previousOnTime;
  
  void setup();
  void update();
  
}

#endif
