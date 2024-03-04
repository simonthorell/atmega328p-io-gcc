//======================================================================
// LED Interface Class Implementation
//======================================================================
#include "hardware_interfaces/led_interface.h"
#include <util/delay.h>
#include <stdlib.h>      // rand() and srand()
#include <time.h>        // Used with srand() to init random seed

//======================================================================
// Public Method: init
// Description:   Initializes the LED pins as outputs
//======================================================================
void LEDInterface::init() {
    // Set LED pins as output
    LEDS_DDR |= (1 << LED_GREEN_BIT) | (1 << LED_RED_BIT) | 
                (1 << LED_BLUE_BIT);
}

//======================================================================
// Public Method: greenOn, greenOff, redOn, redOff, blueOn, blueOff
// Description:   Turn on or off the specified LED
//======================================================================

void LEDInterface::greenOn() {
    LEDS_PORT |= (1 << LED_GREEN_BIT);
}

void LEDInterface::greenOff() {
    LEDS_PORT &= ~(1 << LED_GREEN_BIT);
}

void LEDInterface::redOn() {
    LEDS_PORT |= (1 << LED_RED_BIT);
}

void LEDInterface::redOff() {
    LEDS_PORT &= ~(1 << LED_RED_BIT);
}

void LEDInterface::blueOn() {
    LEDS_PORT |= (1 << LED_BLUE_BIT);
}

void LEDInterface::blueOff() {
    LEDS_PORT &= ~(1 << LED_BLUE_BIT);
}

//======================================================================
// Public Method: lightShow
// Description:   Make the LEDs do a random light show.
//======================================================================
void LEDInterface::lightShow() {
    srand(time(NULL)); // Random seed generator

    for (int i = 0; i < 100; i++) { // Run the loop 100 times
        int action = rand() % 6;    // Random number between 0 and 5
        
        switch (action) {
            case 0: this->greenOn();  break;
            case 1: this->greenOff(); break;
            case 2: this->redOn();    break;
            case 3: this->redOff();   break;
            case 4: this->blueOn();   break;
            case 5: this->blueOff();  break;
        }

        // Random delay between 50 and 200 milliseconds
        int delayTime = (rand() % 171) + 30;
        for(int delay = 0; delay < delayTime; delay += 10) {
            _delay_ms(10);
        }
    }

    // Turn off all LEDs when complete
    this->greenOff();
    this->redOff();
    this->blueOff();
}