#ifndef BEEPER_H
#define BEEPER_H

#include "settings.h"
#include "display.h"

namespace Beeper {
  
  void setup();
  void beep();
  void beep(uint8_t duration);
  
}

#endif


