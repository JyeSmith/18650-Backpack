#include "beeper.h"

namespace Beeper {
    
  void setup() {
    
    pinMode(pinBeeper, OUTPUT);
    digitalWrite(1, LOW);
    
    // Morse code "on" --- -.
    beep(beepDuration*2);delay(beepDuration);
    beep(beepDuration*2);delay(beepDuration);
    beep(beepDuration*2);delay(beepDuration);
    delay(beepDuration*2);delay(beepDuration);
    beep(beepDuration*2);delay(beepDuration);
    beep(beepDuration);delay(beepDuration);
    
  }

  void beep() {
    
    digitalWrite(pinBeeper, HIGH);
    Display::clear();
    Display::switchFrame();
    delay(beepDuration);
    digitalWrite(pinBeeper, LOW);
    Display::switchFrame();
    
  }
  
  void beep(uint8_t duration) {
    
    digitalWrite(pinBeeper, HIGH);
    delay(duration);
    digitalWrite(pinBeeper, LOW);
    
  }

}
