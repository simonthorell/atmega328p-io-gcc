#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include <avr/io.h>        // AVR register definitions
#include <avr/interrupt.h> // AVR interrupt definitions
#include "mcu_mapping.h"   // Button pin definitions

// LED interface for controlling LEDs
#include "hardware_interfaces/led_interface.h"

// Use to debouce buttons
typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED,
    BUTTON_UNKOWN
} ButtonStatus;

class ButtonInterface {
public:
    ButtonInterface(LEDInterface& ledInterface);
    void checkButtons();

private:
    // Reference to LEDInterface for controlling LEDs
    LEDInterface& LED;

    // Check button status and debounce
    ButtonStatus buttonDebounce(unsigned char btn);

    // Private methods to read the state of each button
    bool readButton1();
    bool readButton2();
    bool readButton3();

    static bool prevButton1State;
    static bool prevButton2State;
    static bool prevButton3State;
};

#endif // BUTTON_INTERFACE_H