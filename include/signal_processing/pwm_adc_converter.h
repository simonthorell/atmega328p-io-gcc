#ifndef PWM_ADC_CONVERTER_H
#define PWM_ADC_CONVERTER_H

#include "hardware_interfaces/adc_interface.h"
#include "hardware_interfaces/pwm_interface.h"

class PwmAdcConverter {
public:
    // Constructor
    PwmAdcConverter(ADCInterface& adc , PWMInterface& pwm);

private:
    // ADC and PWM interfaces objects
    ADCInterface& adc;
    PWMInterface& pwm;
};

#endif // PWM_ADC_CONVERTER_H