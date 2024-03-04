//======================================================================
// Potentiometer (POT) Interface Class Implementation
//======================================================================
#include "hardware_interfaces/pot_interface.h"
#include "pin_map.h"

//======================================================================
// Constructor
//======================================================================
POTInterface::POTInterface() {}

//======================================================================
// Public Method: readValue
// Description:   Read the value of the potentiometer
//======================================================================
int POTInterface::readValue() {
    // Configure ADC with AVCC as reference voltage and set the potentiometer channel
    CONFIGURE_ADC_FOR_CHANNEL(POTENTIOMETER_CHANNEL);

    // Start the conversion, wait for completion, and return the result as previously shown
    ADC_START_CONVERSION();
    while (!ADC_IS_CONVERSION_COMPLETE());
    return ADC;
}