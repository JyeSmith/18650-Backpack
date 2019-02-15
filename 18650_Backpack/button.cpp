#include "button.h"
#include "display.h"
#include "at24c02_eeprom.h"

namespace Buttons {

  bool buttonModePressed = false;
  bool buttonChangePressed = false;
  
  void setup() {

    pinMode(buttonMode, INPUT_PULLUP);
    pinMode(buttonChange, INPUT_PULLUP);
    
  }
      
  void update() {

    if (buttonModePressed) {

      // Cycle through callsign character selection
      if (Display::displayState == Display::callSignScreenChar && Display::callSignLetterSelected < 11) {
        Display::callSignLetterSelected++;
      } else {
        Display::displayState = (Display::displayStatEnum)(Display::displayState + 1);
        Display::callSignLetterSelected = 0;
      }

      // Cycle through displayStates
      if (Display::displayState == Display::maxEnum) {
        Display::displayState = Display::homeScreen;
      }

      Display::update();
      
      Beeper::beep(beepDuration);
      
    }
    
    if (buttonChangePressed) {
      
      switch (Display::displayState) {
        
        // Do nothing when on homeScreen
        case Display::homeScreen:
          break;

        // Change cell alarm voltage
        case Display::batteryAlarmScreen:
          EepromSettings.alarmVoltage += 5;
          if (EepromSettings.alarmVoltage > 400) {
            EepromSettings.alarmVoltage = 250;
          }
          EepromSettings.save();
          break;

        // Change callsign characters
        case Display::callSignScreenChar:
          EepromSettings.callSign[Display::callSignLetterSelected] += 1;
          if (EepromSettings.callSign[Display::callSignLetterSelected] > 90) {
            EepromSettings.callSign[Display::callSignLetterSelected] = 45;
          }
          EepromSettings.save();
          break;
          
      }   
      
      Display::update();
      
      Beeper::beep(beepDuration);

    }
  
    buttonModePressed = false;
    buttonChangePressed = false;
  
  }
  
}
