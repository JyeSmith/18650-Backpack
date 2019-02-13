#ifndef TIMER_H
#define TIMER_H

class Timer {
  private:
    uint32_t nextTick;
    uint16_t delay;
    bool ticked;

  public:
    Timer(uint16_t delay);
    const bool hasTicked();
    void reset();
};

#endif


