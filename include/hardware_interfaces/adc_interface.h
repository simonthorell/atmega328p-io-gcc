#ifndef ADCInterface_H
#define ADCInterface_H

#include <stdint.h>

class ADCInterface {
public:
    ADCInterface(); // Constructor to initialize the ADC
    void Init(); // Method to initialize ADC settings
    uint16_t Read(uint8_t ch); // Method to read from a specific ADC channel
};

#endif // ADCInterface_H