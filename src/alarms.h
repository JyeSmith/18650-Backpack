#ifndef ALARMS_H
#define ALARMS_H

#include "settings.h"
#include "timer.h"

namespace Alarms {

  extern bool isBatteryAlarmOn;
  extern bool isBatteryAlarmCritical;

  extern Timer alarmUpdate;
  extern Timer alarmUpdateCritical;
  
  void setup();
  void update();
  
}

#endif
