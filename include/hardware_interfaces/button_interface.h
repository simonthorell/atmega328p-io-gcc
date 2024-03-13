#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include <avr/io.h>        // AVR register definitions
#include <avr/interrupt.h> // AVR interrupt definitions
#include "mcu_mapping.h"   // Button pin definitions

// LED interface for controlling LEDs
#include "hardware_interfaces/led_interface.h"

// Define which type of interupt to use
typedef enum {
    TIMER_2_INTERUPT,
    PIN_CHANGE_INTERUPT
} ButtonInteruptType;

// Use to debouce buttons
typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED,
    BUTTON_BOUNCING
} ButtonStatus;

class ButtonInterface {
public:
    // Constructor
    ButtonInterface(LEDInterface& ledInterface);

    // Static instance for static methods to access non-static methods
    static ButtonInterface* instance;

    // Variable to set interupt type & debounce bitMask
    ButtonInteruptType interuptType;
    unsigned char debounceBitMask;

    // Public Setters
    void setInterruptType(ButtonInteruptType type);

    // Static method to update button states in the ISR
    static void updateButtonStates();

    // Make public to allow serial debugging of button states
    static volatile unsigned char buttonStates[BUTTONS_COUNT];
    static volatile unsigned char lastButtonStates[BUTTONS_COUNT];

private:
    // Reference to LEDInterface for controlling LEDs
    LEDInterface& LED;

    // Define static variables for button states and debouncing
    static const unsigned char buttonBits[BUTTONS_COUNT];

    // Private methods to read and handle button actions
    bool readButton(unsigned char buttonBit);
    ButtonStatus buttonDebounce(unsigned char btn);
    void handleButtonAction(int buttonIndex);

};

#endif // BUTTON_INTERFACE_H