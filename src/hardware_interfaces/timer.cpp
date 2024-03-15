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
            // Millis Timer
            TCCR1A = 0; // Set entire TCCR1A register to 0
            TCCR1B = 0; // Same for TCCR1B
            TCCR1B |= (1 << CS11) | (1 << CS10); // Set prescaler to 64
            TIMSK1 |= (1 << TOIE1); // Enable overflow interrupt
            // Preload timer for 1ms interrupts
            TCNT1 = 0xFF06; // 65536 - 250 = 65286 (0xFF06)
            break;
        case TIMER2:
            // Overflow Timer
            TCCR2A = 0;            // Init Timer2A
            TCCR2B = 0;            // Init Timer2B
            TCCR2B |= 0B00000111;  // Prescaler = 1024
            TCNT2 = 5;             // Timer Preloading
            TIMSK2 |= 0B00000001;  // Enable Timer Overflow Interrupt
            break;
    }
}