#include <Arduino.h>
#include <avr/pgmspace.h>
#include "beeper.h"
#include "timer.h"
#include "at24c02_eeprom.h"

namespace Alarms {

  bool isBatteryAlarmOn = false;
  bool isBatteryAlarmCritical = false;

  Timer alarmUpdate = Timer(alarmUpdatePeriod);
  Timer alarmUpdateCritical = Timer(alarmUpdatePeriodCritical);
    
  void setup() {
    
  }
    
  void update() {
    
    if (Voltage::voltageCellOne*100 < EepromSettings.alarmVoltage || Voltage::voltageCellTwo*100 < EepromSettings.alarmVoltage) {
      isBatteryAlarmOn = true;
    }
    else if (Voltage::voltageCellOne*100 > EepromSettings.alarmVoltage+alarmHysteresis && Voltage::voltageCellTwo*100 > EepromSettings.alarmVoltage+alarmHysteresis) {
      isBatteryAlarmOn = false ;
    }
    
//    if (Voltage::voltageCellOne*100 < EepromSettings.alarmVoltageCritical || Voltage::voltageCellTwo*100 < EepromSettings.alarmVoltageCritical) {
    if (Voltage::voltageCellOne*100 < EepromSettings.alarmVoltage-10 || Voltage::voltageCellTwo*100 < EepromSettings.alarmVoltage-10) {
      isBatteryAlarmCritical = true;
    }
    else if (Voltage::voltageCellOne*100 > EepromSettings.alarmVoltage-10+alarmHysteresis && Voltage::voltageCellTwo*100 > EepromSettings.alarmVoltage-10+alarmHysteresis) {
      isBatteryAlarmCritical = false ;
    }
  
    if (isBatteryAlarmCritical && alarmUpdateCritical.hasTicked()) {
      alarmUpdateCritical.reset();
      Beeper::beep();
    } 
    else if (isBatteryAlarmOn && alarmUpdate.hasTicked()) {
      alarmUpdate.reset();
      Beeper::beep();
    }
  
  }

}




