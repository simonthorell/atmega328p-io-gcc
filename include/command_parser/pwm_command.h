#ifndef PWM_COMMAND_H
#define PWM_COMMAND_H

#include <string.h>
#include "data_transmission/usart.h"
#include "hardware_interfaces/adc_interface.h"
#include "hardware_interfaces/pwm_interface.h"

class CommandParser; // Forward Declaration

class PWMCommand {
    // Restrict Access to CommandParser
    friend class CommandParser;

public:
    // Constructor
    PWMCommand(USART &serial, ADCInterface& adc, PWMInterface& pwm) 
        : serial(serial), adc(adc), pwm(pwm) {}

    // Methods Accessible to CommandParser
    void execute(const char* command);

private:
    // Hardware Interface Objects
    USART& serial;
    ADCInterface& adc;
    PWMInterface& pwm;

    // Private Methods
    void potControlLED();
    void commandControlLED(PWMInterface& pwm, const char* command);
    void adcControlPwm(USART& serial, PWMInterface& pwm, 
                       ADCInterface& adc, const char* command);
    void adcAutoAdjustPwm(USART& serial, PWMInterface& pwm, 
                          ADCInterface& adc, const char* command);

    // Convert input value and scale it to a new range (ADC to PWM cycle)
    long map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
};

#endif // PWM_COMMAND_H