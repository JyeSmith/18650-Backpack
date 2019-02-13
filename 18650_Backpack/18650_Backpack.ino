/*
MIT License

Copyright (c) 2019 Jye Smith

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <TinyWireM.h>
#include "voltage.h"
#include "display.h"
#include "beeper.h"
#include "button.h"
#include "alarms.h"
#include "time.h"
#include "timer.h"
#include "at24c02_eeprom.h"

void setup() {

  TinyWireM.begin();
  
  Buttons::setup(); // Setup buttons first so they can be read during eeprom

  EepromSettings.load();

  Time::setup();

  Voltage::setup();
  Display::setup();

  Voltage::update();
  Display::update();

  Beeper::setup();

  // Interrupt for buttons
  GIMSK = 0b00100000;    // turns on pin change interrupts
  PCMSK = 0b00011000;    // turn on interrupts on pins PB3 and PB4
  sei();

}

void loop() {

  Time::update();
  Buttons::update();
  Voltage::update();
  Alarms::update();
  Display::update();
  
}

// Button interrupt function
ISR(PCINT0_vect) {

  if (!digitalRead(buttonMode)) {
    Buttons::buttonModePressed = true;
  }
  else if (!digitalRead(buttonChange)) {
    Buttons::buttonChangePressed = true;
  }

}
