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
    // Config ADC with AVCC as reference voltage and set the pot channel
    CONFIGURE_ADC_FOR_CHANNEL(POTENTIOMETER_CHANNEL);
    
    ADC_START_CONVERSION();                 // Start the conversion
    while (!ADC_IS_CONVERSION_COMPLETE());  // Wait for conversion
    return ADC;                             // Return the ADC value
}