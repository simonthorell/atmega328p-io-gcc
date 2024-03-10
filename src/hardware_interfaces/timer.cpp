//==============================================================================
// Timer Class Implementation
//==============================================================================
#include "hardware_interfaces/timer.h"
#include <avr/io.h>

//==============================================================================
// Constructor
//==============================================================================
Timer::Timer(TimerType type) : timerType(type) {
    init();
}

//==============================================================================
// Public Methods: init
// Description:    Initializes the timer based on the timer type
//==============================================================================
void Timer::init() {
    switch (timerType) {
        case TIMER0:
            // TODO: Add setup code if timer 0 is needed later...
            break;
        case TIMER1:
            // TODO: Add setup code if timer 1 is needed later...
            break;
        case TIMER2:
            TCCR2A = 0;            // Init Timer2A
            TCCR2B = 0;            // Init Timer2B
            TCCR2B |= 0B00000111;  // Prescaler = 1024
            TCNT2 = 5;             // Timer Preloading
            TIMSK2 |= 0B00000001;  // Enable Timer Overflow Interrupt
            break;
    }
}