#ifndef ADCInterface_H
#define ADCInterface_H

#include <stdint.h>

class ADCInterface {
public:
    // Constructor
    ADCInterface();

    // Public Method to read from a specific ADC channel
    uint16_t Read(uint8_t ch); 
};

#endif // ADCInterface_H