#ifndef VOLTAGE_H
#define VOLTAGE_H

#include "Adafruit_INA219.h"
#include "settings.h"
#include "time.h"
#include "timer.h"

namespace Voltage {
  
  extern Adafruit_INA219 ina219Batt;
  extern Adafruit_INA219 ina219Cell;

  extern float voltageCellOne;
  extern float voltageCellTwo;
  extern float voltageBattery;
  extern float current;
//  extern float mAh;
  extern uint32_t previousmAhUpdateTime;
  extern Timer mAhUpdate;
  
  void setup();
  void update();
  
}

#endif
