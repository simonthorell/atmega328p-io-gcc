//==============================================================================
// ADCCommand Class Implementation
//==============================================================================
#include "command_parser/adc_command.h"
#include <util/delay.h> // _delay_ms
#include <string.h>     // strcmp
#include <stdio.h>      // snprintf

//=============================================================================
// Public Methods: execute()
// Description: Execute the ADC command using the ADC Hardware Interface.
// Restriction: Accessible in CommandParser Class Only
//=============================================================================
void ADCCommand::execute(const char* command) {
    if (strcmp(command, "adc read pot") == 0) {
        char buffer[128];

        while (1) {
            // Read ADC value and convert to voltage
            uint16_t adcValue = adc.readADC(POT_ADC_CHANNEL);
            float voltage = adcValue * 5.0 / 1023.0; // Convert to voltage


            // Manually convert the voltage to a string
            int voltage_int = static_cast<int>(voltage);
            int voltage_frac = static_cast<int>((voltage - voltage_int) * 100);

            snprintf(buffer, sizeof(buffer), 
                     "ADC Value: %d, Voltage: %d.%02dV\r\n", 
                     adcValue, voltage_int, voltage_frac
                    );
            serial.print(buffer);

            // Wait for 300 milliseconds before next reading
            _delay_ms(300);

            // Exit when pot is turned to 0
            if (voltage == 0) {
                return;
            }
        }
    }
}