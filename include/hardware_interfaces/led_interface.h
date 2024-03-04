#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

class LEDInterface {
public:
    // Initializes the LEDs
    void init();
    
    // Functions to control the state of each LED
    void greenOn();
    void greenOff();
    void redOn();
    void redOff();
    void blueOn();
    void blueOff();

    // TODO: Methods to make "light show"
};

#endif // LED_INTERFACE_H