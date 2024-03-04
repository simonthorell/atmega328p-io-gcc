//======================================================================
// Buttons Interface Class Implementation
//======================================================================
#include "hardware_interfaces/button_interface.h"
#include <util/delay.h>  // For debouncing

#define DEBOUNCE_DELAY 80 // Debounce delay in milliseconds

//======================================================================
// Constructor
//======================================================================
ButtonInterface::ButtonInterface(LEDInterface& LED) : LED(LED) {
    // Set the button pins as input
    DDRB &= ~((1 << BUTTON_1_BIT) | (1 << BUTTON_2_BIT) | 
              (1 << BUTTON_3_BIT));
    
    // Enable pull-up resistors
    PORTB |= (1 << BUTTON_1_BIT) | (1 << BUTTON_2_BIT) | 
             (1 << BUTTON_3_BIT);
}

//======================================================================
// Public Methods: readButton1, readButton2, readButton3
// Description:    Reads the state of each button
//======================================================================
bool ButtonInterface::readButton1() {
    return !(PINB & (1 << BUTTON_1_BIT));
}

bool ButtonInterface::readButton2() {
    return !(PINB & (1 << BUTTON_2_BIT));
}

bool ButtonInterface::readButton3() {
    return !(PINB & (1 << BUTTON_3_BIT));
}

//======================================================================
// Public Method: checkButtons
// Description:   Checks the state of each button and debounces the 
//                input.
//======================================================================
void ButtonInterface::checkButtons() {
    static bool prevButton1State = false;
    static bool prevButton2State = false;
    static bool prevButton3State = false;

    // Check and debounce button 1
    if (readButton1() != prevButton1State) {
        _delay_ms(DEBOUNCE_DELAY);
        if (readButton1() != prevButton1State) {
            prevButton1State = readButton1();
            if (prevButton1State) {
                LED.greenToggle(); // Assuming a toggle method exists
            }
        }
    }

    // Check and debounce button 2
    if (readButton2() != prevButton2State) {
        _delay_ms(DEBOUNCE_DELAY);
        if (readButton2() != prevButton2State) {
            prevButton2State = readButton2();
            if (prevButton2State) {
                LED.redToggle(); // Assuming a toggle method exists
            }
        }
    }

    // Check and debounce button 3
    if (readButton3() != prevButton3State) {
        _delay_ms(DEBOUNCE_DELAY);
        if (readButton3() != prevButton3State) {
            prevButton3State = readButton3();
            if (prevButton3State) {
                LED.blueToggle(); // Assuming a toggle method exists
            }
        }
    }
}