//======================================================================
// Buttons Interface Class Implementation
//======================================================================
#include "hardware_interfaces/button_interface.h"
#include <util/delay.h>

// TODO: Improve ISR for button interface
static ButtonInterface* buttonInterfaceInstance = nullptr;

bool ButtonInterface::prevButton1State = false;
bool ButtonInterface::prevButton2State = false;
bool ButtonInterface::prevButton3State = false;

#define BUTTON_DEBOUNCE_DELAY 80 // ms

ISR(BUTTON_ISR_VECT) {
    if (buttonInterfaceInstance != nullptr) {
        buttonInterfaceInstance->checkButtons();
    }
}

//======================================================================
// Constructor
//======================================================================
ButtonInterface::ButtonInterface(LEDInterface& ledInterface) : LED(ledInterface) {
    buttonInterfaceInstance = this; // Set the static or global instance pointer

    // Set the button pins as input
    BUTTONS_DDR &= ~((1 << BUTTON_1_BIT) | (1 << BUTTON_2_BIT) | 
                     (1 << BUTTON_3_BIT));
    
    // Enable pull-up resistors
    BUTTONS_PORT |= (1 << BUTTON_1_BIT) | (1 << BUTTON_2_BIT) | 
                    (1 << BUTTON_3_BIT);

    // Enable pin change interrupt for PCINT0 Group (D8-D13)
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3);

    /* Note: Global Interupts 'sei()' are enabled in main.cpp */

    // Turn off the LEDs
    LED.greenOff();
    LED.redOff();
    LED.blueOff();
}

//======================================================================
// Public Methods: readButton1, readButton2, readButton3
// Description:    Reads the state of each button
//======================================================================
bool ButtonInterface::readButton1() {
    return !(BUTTONS_PIN & (1 << BUTTON_1_BIT));
}

bool ButtonInterface::readButton2() {
    return !(BUTTONS_PIN & (1 << BUTTON_2_BIT));
}

bool ButtonInterface::readButton3() {
    return !(BUTTONS_PIN & (1 << BUTTON_3_BIT));
}

//======================================================================
// Public Method: checkButtons
// Description:   Checks the state of each button and debounces the 
//                input.
//======================================================================
void ButtonInterface::checkButtons() {
    _delay_ms(BUTTON_DEBOUNCE_DELAY);

    bool currentButton1State = readButton1();
    if (currentButton1State != prevButton1State) {
        prevButton1State = currentButton1State;
        if (prevButton1State) {
            LED.greenToggle();
        }
    }

    bool currentButton2State = readButton2();
    if (currentButton2State != prevButton2State) {
        prevButton2State = currentButton2State;
        if (prevButton2State) {
            LED.redToggle();
        }
    }

    bool currentButton3State = readButton3();
    if (currentButton3State != prevButton3State) {
        prevButton3State = currentButton3State;
        if (prevButton3State) {
            LED.blueToggle();
        }
    }
}