//=======================================================================
// PWM => ADC Converter Class Implementation
//=======================================================================
#include "signal_processing/pwm_adc_converter.h"
#include <avr/io.h>
#include <util/delay.h>

//=======================================================================
// Constructor 
//=======================================================================
PwmAdcConverter::PwmAdcConverter(ADCInterface& adc , PWMInterface& pwm) 
    : adc(adc), pwm(pwm) {
}

//=======================================================================
// TODO: Convert PWM value to ADC signal
//=======================================================================
// TODO: Implement...