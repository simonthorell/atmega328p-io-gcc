//======================================================================
// Potentiometer (POT) Interface Class Implementation
//======================================================================
#include "hardware_interfaces/pot_interface.h"

//======================================================================
// Constructor
//======================================================================
POTInterface::POTInterface() {}

//======================================================================
// Public Method: readValue
// Description:   Read the value of the potentiometer
//======================================================================
int POTInterface::readValue() {
    /* TODO: Should these registers be added in 'pin_map.h' or not? */

    // Set the ADC multiplexer to the potentiometer channel
    ADMUX = (1 << REFS0) | POTENTIOMETER_CHANNEL;

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Return the result
    return ADC;
}