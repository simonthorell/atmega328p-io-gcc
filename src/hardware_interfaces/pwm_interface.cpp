//==============================================================================
// PWM Interface Class Implementation
//==============================================================================
#include "hardware_interfaces/pwm_interface.h"

//==============================================================================
// Constructor
//==============================================================================
PWMInterface::PWMInterface() {
    // Set PWM pin as output
    PWM_OUTPUT_DDR |= (1 << PWM_OUTPUT_BIT);
    
    // Set Fast PWM mode with non-inverted output
    PWM_TCCRA |= (1 << PWM_WGMx1) | (1 << PWM_WGMx0) | (1 << PWM_COMx1);
    PWM_TCCRB &= ~(1 << WGM22); // If needed, based on your timer

    // Set initial PWM frequency (prescaler)
    PWM_TCCRB |= (1 << PWM_CSx1); // Example: clk/8 prescaler

    // Set initial duty cycle
    setDutyCycle(255); // Max duty cycle (0-255)
}

//==============================================================================
// Public Method: setDutyCycle
// Description:   Set the duty cycle of the PWM signal
//==============================================================================
void PWMInterface::setDutyCycle(uint8_t duty) {
    // Set duty cycle (0 to 255)
    PWM_OUTPUT_OC = duty;
}