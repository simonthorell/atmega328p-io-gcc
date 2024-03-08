#ifndef PWM_ADC_CONVERTER_H
#define PWM_ADC_CONVERTER_H

#include "hardware_interfaces/adc_interface.h"
#include "hardware_interfaces/pwm_interface.h"

class PwmAdcConverter {
public:
    // Constructor
    PwmAdcConverter(ADCInterface& adc , PWMInterface& pwm);

    // Setter & Getter methods
    uint16_t getPwmAdcReading();
    void setPwmDutyCycle(uint8_t dutyCycle);

private:
    // ADC and PWM interfaces objects
    ADCInterface& adc;
    PWMInterface& pwm;
};

#endif // PWM_ADC_CONVERTER_H