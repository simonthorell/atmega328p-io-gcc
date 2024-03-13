//==============================================================================
// PWM Interface Class Implementation
//==============================================================================
#include "hardware_interfaces/pwm_interface.h"

const float PROPORTIONAL_GAIN = 0.1; // Gain for proportional control

//==============================================================================
// Constructor
//==============================================================================
PWMInterface::PWMInterface() {
    // Set PWM pin as output
    PWM_OUTPUT_DDR |= (1 << PWM_OUTPUT_BIT);
    
    // Set Fast PWM mode with non-inverted output
    PWM_TCCRA |= (1 << PWM_WGMx1) | (1 << PWM_WGMx0) | (1 << PWM_COMx1);
    PWM_TCCRB &= ~(1 << WGM22);

    // Set initial PWM frequency (prescaler)
    PWM_TCCRB |= (1 << PWM_CSx1); // clk/8 prescaler
 
    // Set initial duty cycle to max (0-255)
    setDutyCycle(255);
}

//==============================================================================
// Public Method: setDutyCycle
// Description:   Set the duty cycle of the PWM signal
//==============================================================================
void PWMInterface::setDutyCycle(uint8_t duty) {
    dutyCycle = duty;      // Save the duty cycle for future adjustments
    PWM_OUTPUT_OC = duty;  // Set duty cycle (0 to 255)
}

void PWMInterface::adjustDutyCycle(int error) {    
    // Calculate the adjustment needed
    int adjustment = (int)(error * PROPORTIONAL_GAIN);
    
    // Calculate the new duty cycle with range (0-255)
    int newDutyCycle = dutyCycle + adjustment;
    if (newDutyCycle > 255) newDutyCycle = 255;
    if (newDutyCycle < 0) newDutyCycle = 0;
    
    // Set the new duty cycle
    setDutyCycle((uint8_t)newDutyCycle);
}