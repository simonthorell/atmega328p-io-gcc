#include "hardware_interfaces/pwm_interface.h"
#include "mcu_mapping.h"

// Constructor
PWMInterface::PWMInterface() {
    this->init();
    setDutyCycle(255); // Max duty cycle
}

void PWMInterface::init() {
    // Set PWM pin as output
    PWM_OUTPUT_DDR |= (1 << PWM_OUTPUT_BIT);
    
    // Set Fast PWM mode with non-inverted output
    PWM_TCCRA |= (1 << PWM_WGMx1) | (1 << PWM_WGMx0) | (1 << PWM_COMx1);
    PWM_TCCRB &= ~(1 << WGM22); // If needed, based on your timer

    // Set initial PWM frequency (prescaler)
    PWM_TCCRB |= (1 << PWM_CSx1); // Example: clk/8 prescaler
}

void PWMInterface::setDutyCycle(uint8_t duty) {
    // Set duty cycle (0 to 255)
    PWM_OUTPUT_OC = duty;
}