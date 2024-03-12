#ifndef ADC_COMMAND_H
#define ADC_COMMAND_H

#include <stdint.h>

#include "data_transmission/usart.h"
#include "hardware_interfaces/adc_interface.h"

class CommandParser; // Forward Declaration

class ADCCommand {
public:
    // Constructor
    ADCCommand(USART& serial, ADCInterface& adcInterface) 
        : serial(serial), adc(adcInterface) {}

    // Public Methods
    void execute(const char* command);

private:
    USART& serial;
    ADCInterface& adc;
};

#endif // ADC_COMMAND_H