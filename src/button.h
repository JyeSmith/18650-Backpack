#ifndef BUTTON_H
#define BUTTON_H

#include "settings.h"
#include "beeper.h"

namespace Buttons {
  
  extern bool buttonModePressed;
  extern bool buttonChangePressed;
  
  void setup();
  void update();
  
}

#endif
