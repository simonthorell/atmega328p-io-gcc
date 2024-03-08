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
// Setters & Getters: setPwmFrequency, setPwmDutyCycle
//=======================================================================
void PwmAdcConverter::setPwmDutyCycle(uint8_t dutyCycle) {
    pwm.setDutyCycle(dutyCycle);
}

uint16_t PwmAdcConverter::getPwmAdcReading() {
    // TODO: Add something....
}