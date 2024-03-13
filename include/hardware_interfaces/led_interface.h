#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "mcu_mapping.h" // LED pin definitions

class LEDInterface {
public:
    // Constructor
    LEDInterface();

    // Functions to toggle the state of each LED
    void greenToggle();
    void redToggle();
    void blueToggle();
    
    // Functions to control the state of each LED
    void greenOn();
    void greenOff();
    void redOn();
    void redOff();
    void blueOn();
    void blueOff();

    // Functions to make the LEDs do a random "light show"
    void lightShow();
};

#endif // LED_INTERFACE_H