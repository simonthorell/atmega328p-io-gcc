#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include <avr/io.h>

class PWMInterface {
public:
    PWMInterface(); // Constructor
    void init(); // Initializes PWM
    void setDutyCycle(uint8_t duty); // Sets the PWM duty cycle
};

#endif // PWM_INTERFACE_H
