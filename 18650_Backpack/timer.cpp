#include <Arduino.h>
#include "timer.h"
#include "time.h"
    
Timer::Timer(uint16_t delay) {
  this->delay = delay;
  this->nextTick = Time::now + this->delay;
  this->ticked = false;
}

const bool Timer::hasTicked() {
  if (this->ticked)
      return true;

  if (Time::now >= this->nextTick) {
      this->ticked = true;
      return true;
  }

  return false;
}

void Timer::reset() {
  this->nextTick = Time::now + this->delay;
  this->ticked = false;
}


