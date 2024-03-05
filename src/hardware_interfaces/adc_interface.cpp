#include "hardware_interfaces/adc_interface.h"
#include <avr/io.h>

ADCInterface::ADCInterface() {
    // Constructor might be left empty or used to automatically initialize the ADC
    Init();
}

void ADCInterface::Init() {
    // AVCC with external capacitor at AREF pin
    ADMUX = (1<<REFS0);
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ADCInterface::Read(uint8_t ch) {
    // Select the corresponding channel 0~7
    ch &= 0b00000111; // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch; // Clears the bottom 3 bits before ORing

    // Start single conversion
    // Write '1' to ADSC
    ADCSRA |= (1<<ADSC);

    // Wait for conversion to complete
    while(ADCSRA & (1<<ADSC));

    return ADC;
}