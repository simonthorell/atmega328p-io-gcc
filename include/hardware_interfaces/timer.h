#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

class Timer {
public:
    enum TimerType {
        TIMER0,
        TIMER1,
        TIMER2
    };

    // Constructor
    Timer(TimerType type);

private:
    TimerType timerType;

    void init();
};

#endif // TIMER_H