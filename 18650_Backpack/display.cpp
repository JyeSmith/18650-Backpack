#include "display.h"
#include <Tiny4kOLED.h>
#include "Font.h"
#include "at24c02_eeprom.h"

namespace Display {

  displayStatEnum displayState = homeScreen;
  uint8_t callSignLetterSelected = 0;
  
  void setup() {
    
    oled.begin();
    oled.clear();
    oled.on();
    oled.switchRenderFrame();
    
  }
      
  void update() {

    switch (displayState) {
      case homeScreen:
        drawHomeScreen();
        break;
      case batteryAlarmScreen:
        drawBatteryAlarmScreen();
        break;
      case callSignScreenChar:
        drawCallSignScreenChar();
        break;        
    }

  }

  void drawBatteryAlarmScreen() {
    oled.clear();
    
    oled.setCursor(0, 0);
//    oled.print(F("SET ALARM VOLTAGE"));
    oled.print(F("SET@ALARM@VOLTAGE"));
//    drawScreenNumber();
    
    oled.setCursor(46, 2);
    oled.print(EepromSettings.alarmVoltage/100.);
    oled.print(F("V"));
    
    oled.switchFrame();
  }
  
  void drawCallSignScreenChar() {
    oled.clear();
    
    oled.setCursor(0, 0);
//    oled.print(F("SET CALLSIGN"));
    oled.print(F("SET@CALLSIGN"));
//    drawScreenNumber();
    
    oled.setCursor(6, 2);
    oled.print(EepromSettings.callSign);
    oled.setCursor(6*(callSignLetterSelected+1), 3);
    oled.print(F("-"));
    
    oled.switchFrame();
  }

//  void drawScreenNumber() {
//    oled.setCursor(103, 3);
//    if ((int)displayState > 9) oled.setCursor(97, 3);
//    oled.print((int)displayState);
//    oled.print(F("/"));
//    oled.print((int)displayStatEnum::maxEnum - 1);    
//  }
  
  void drawHomeScreen() {
  
    oled.clear();
  
    oled.setFont(&font);

    // Callsign
    oled.setCursor(0, 0);
    oled.print(EepromSettings.callSign);    

    // On Time
    oled.setCursor(79, 0);

    if (Time::now/3600000 < 10) oled.print(F("0"));  
    oled.print(Time::now/3600000);
    oled.print(F(":"));  
    
    if (Time::now%3600000/60000 < 10) oled.print(F("0"));  
    oled.print(Time::now%3600000/60000);
    oled.print(F(":"));  
    
    if (Time::now%60000/1000 < 10) oled.print(F("0"));  
    oled.print(Time::now%60000/1000);

    // Line
    oled.setCursor(0, 1);
    for (uint8_t i=0; i<21; i++) {
      oled.print(F("-"));
    }
    
    // Battery and cell voltages
    oled.setCursor(0, 2);
    oled.print(Voltage::voltageBattery);
    oled.print(F("V"));
//    oled.print(F(" ("));
    oled.print(F("@>"));
    oled.print(Voltage::voltageCellOne);
    oled.print(F("V"));
//    oled.print(F(" + "));
    oled.print(F("@-@"));
    oled.print(Voltage::voltageCellTwo);
    oled.print(F("V"));
//    oled.print(F(")"));
    oled.print(F("?"));

    // mAh
    oled.setCursor(0, 3);
    if (EepromSettings.mAh < 10) {
      oled.print(EepromSettings.mAh);
    } else {
      oled.print((uint16_t)EepromSettings.mAh);
    }
    oled.print(F(";"));    // this is lowercase 'm'
    oled.print(F("A"));  
    oled.print(F("<"));    // this is lowercase 'h'

    // Current
    if (Voltage::current < 100) {
      oled.setCursor(83, 3);
      oled.print(Voltage::current);
    } else if (Voltage::current < 1000){
      oled.setCursor(95, 3);
      oled.print((uint16_t)Voltage::current);
    } else {
      oled.setCursor(89, 3);
      oled.print((uint16_t)Voltage::current);
    }
    oled.print(F(";"));    // this is lowercase 'm'
    oled.print(F("A"));
      
    oled.switchFrame();
  
  }

  void clear() {
    oled.clear();
  }
  
  void switchFrame() {
    oled.switchFrame();
  }
  
}
