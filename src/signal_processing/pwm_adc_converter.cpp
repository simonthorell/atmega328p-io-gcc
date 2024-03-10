//=======================================================================
// PWM => ADC Converter Class Implementation
//=======================================================================
#include "signal_processing/pwm_adc_converter.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define AUTO_MV_THRESHOLD 4500       // Maximum millivolts for auto-adjustment
#define DUTY_CYCLE_MV_FACTOR 19.6078 // 5000mV / 255 (8-bit resolution)
#define TOLERANCE 10                 // Tolerance for auto-adjustment

//=======================================================================
// Constructor 
//=======================================================================
PwmAdcConverter::PwmAdcConverter(ADCInterface& adc , PWMInterface& pwm) 
    : adc(adc), pwm(pwm) {
}

//=======================================================================
// Private Methods: setPwmDutyCycle, autoAdjustPwm
//=======================================================================
void PwmAdcConverter::autoAdjustPwm(uint16_t desiredMilliVolts) {
    // Auto adjust any value above threshold to the maximum
    if(desiredMilliVolts > AUTO_MV_THRESHOLD) desiredMilliVolts = AUTO_MV_THRESHOLD; 

    uint16_t currentAdcReading = adc.readADC(PWM_ADC_CHANNEL);
    currentAdcReading = (currentAdcReading * 5000) / 1023; // Convert to millivolts

    int error = desiredMilliVolts - (currentAdcReading);

    // Keep adjusting until reading is within set tolerance
    while(abs(error) > TOLERANCE) {
        int newVoltage = currentAdcReading + error;

        pwm.setPwmVoltage(newVoltage);

        currentAdcReading = adc.readADC(PWM_ADC_CHANNEL);
        currentAdcReading = (currentAdcReading * 5000) / 1023; // Convert to millivolts
        error = desiredMilliVolts - (currentAdcReading);

        _delay_ms(10);
    }

}