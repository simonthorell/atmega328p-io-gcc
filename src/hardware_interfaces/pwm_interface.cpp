//==============================================================================
// PWM Interface Class Implementation
//==============================================================================
#include "hardware_interfaces/pwm_interface.h"
#include <math.h>

#define MIN_MILLI_VOLTAGE 0          // Min voltage is 0V
#define MAX_MILLI_VOLTAGE 5000       // Max voltage is 5V
#define DUTY_CYCLE_MV_FACTOR 19.6078 // 5000mV / 255 (8-bit resolution)

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

void PWMInterface::setPwmVoltage(uint16_t milliVolts) {
    if (milliVolts >= MIN_MILLI_VOLTAGE && milliVolts <= MAX_MILLI_VOLTAGE) {
        // Perform calculation in floating-point to avoid precision loss
        float dutyCycle = round(milliVolts / DUTY_CYCLE_MV_FACTOR);
        
        // Ensure the duty cycle is within bounds after rounding
        if (dutyCycle > 255) dutyCycle = 255;
        else if (dutyCycle < 0) dutyCycle = 0;
        
        // Convert to integer and set the duty cycle
        setDutyCycle(static_cast<int>(dutyCycle));
    }
}