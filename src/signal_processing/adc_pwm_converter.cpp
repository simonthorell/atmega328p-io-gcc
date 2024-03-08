//=======================================================================
// ADC PWM Converter Class Implementation
//=======================================================================
#include "signal_processing/adc_pwm_converter.h"
#include <avr/io.h>
#include <util/delay.h>

//=======================================================================
// Constructor 
//=======================================================================
AdcPwmConverter::AdcPwmConverter(ADCInterface& adc , PWMInterface& pwm) 
    : adc(adc), pwm(pwm) {
}

//=======================================================================
// TODO: Convert ADC value to PWM signal
//=======================================================================
// TODO: Implement the function to convert the ADC value to PWM signal