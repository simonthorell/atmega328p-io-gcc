#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include <avr/io.h>  // AVR register definitions
#include "mcu_mapping.h" // Button pin definitions

// LED interface for controlling LEDs
#include "hardware_interfaces/led_interface.h"

class ButtonInterface {
public:
    ButtonInterface(LEDInterface& ledInterface);
    void checkButtons();

private:
    // Reference to LEDInterface for controlling LEDs
    LEDInterface& LED;

    // Private methods to read the state of each button
    bool readButton1();
    bool readButton2();
    bool readButton3();
};

#endif // BUTTON_INTERFACE_H