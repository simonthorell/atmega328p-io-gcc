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

    // Public Variables
    static volatile unsigned char buttonStates[BUTTONS_COUNT];
    static volatile bool actionTriggered;
    ButtonInteruptType interuptType;

    // Public Setter Methods
    void setInterruptType(ButtonInteruptType type);

    // Static methods to update button states in the ISR
    static void updateButtonStatesOnTimerOverflow();
    static void updateButtonStatesOnPinChange(unsigned long currentTime);

private:
    // Reference to LEDInterface for controlling LEDs
    LEDInterface& LED;

    // Array for the button register bits
    static const unsigned char buttonBits[BUTTONS_COUNT];

    // Private methods
    bool readButton(unsigned char buttonBit);
    void setButtonState(int buttonIndex);
    void resetButtonStates();
    void handleButtonAction(int buttonIndex);
    ButtonStatus buttonDebounce(unsigned char btn);

};

#endif // BUTTON_INTERFACE_H