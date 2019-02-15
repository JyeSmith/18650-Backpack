#include "voltage.h"
#include "at24c02_eeprom.h"
        
namespace Voltage {

  Adafruit_INA219 ina219Batt;
  Adafruit_INA219 ina219Cell;
  
  float voltageCellOne = 0;
  float voltageCellTwo = 0;
  float voltageBattery = 0;
  float current = 0;
  uint32_t previousmAhUpdateTime = 0;
  
  Timer mAhUpdate = Timer(mAhUpdatePeriod);
  
  void setup() {

    previousmAhUpdateTime = Time::now;
    
    ina219Batt.begin(0b1000101);    // A0+A1=+5v
    ina219Batt.setCalibration_32V_1A();
  
    ina219Cell.begin(0b1000000);    // A0+A1=GND
    ina219Cell.setCalibration_32V_1A();
    
  }
      
  void update() {

    float shuntVoltage = 0;
    float busVoltage = 0;
    voltageCellOne = 0;
    voltageCellTwo = 0;
    voltageBattery = 0;
    current = 0;
  
    for (uint8_t i = 0; i < 8; i++) {
      shuntVoltage += ina219Batt.getShuntVoltage_mV();
      busVoltage += ina219Batt.getBusVoltage_V();
      current += ina219Batt.getCurrent_mA();
    }
    shuntVoltage /= 8;
    busVoltage /= 8;
    current /= 8;
    
    voltageBattery = busVoltage + (shuntVoltage/1000);
  
    for (uint8_t i = 0; i < 8; i++) {
      voltageCellOne += ina219Cell.getBusVoltage_V();
    }
    voltageCellOne /= 8;
    
    if (voltageBattery > voltageCellOne) {
      voltageCellTwo = voltageBattery - voltageCellOne;
    } else {
      voltageCellTwo = 0;
    }

    if (mAhUpdate.hasTicked()) {
      mAhUpdate.reset();
      EepromSettings.mAh += ( current / 3600 ) * ( (Time::now-previousmAhUpdateTime) / 1000.0 ); 
      previousmAhUpdateTime = Time::now;
      EepromSettings.save();
    }
  
  }
    
}
