#ifndef ADC_PWM_CONVERTER_H
#define ADC_PWM_CONVERTER_H

#include "hardware_interfaces/adc_interface.h"
#include "hardware_interfaces/pwm_interface.h"

class AdcPwmConverter {
public:
    // Constructor
    AdcPwmConverter(ADCInterface& adc , PWMInterface& pwm);

private:
    // ADC and PWM interfaces objects
    ADCInterface& adc;
    PWMInterface& pwm;
};

#endif // ADC_PWM_CONVERTER_H