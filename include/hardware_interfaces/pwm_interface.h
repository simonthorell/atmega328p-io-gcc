#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include <avr/io.h>
#include "mcu_mapping.h"

class PWMInterface {
public:
    // Constructor
    PWMInterface(); // Constructor

    // Set the duty cycle of the PWM signal
    void setDutyCycle(uint8_t duty); 
};

#endif // PWM_INTERFACE_H
