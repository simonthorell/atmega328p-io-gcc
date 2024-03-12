//=============================================================================
// PWMCommand Class Implementation
//=============================================================================
#include "command_parser/pwm_command.h"
#include <util/delay.h> // _delay_ms
#include <string.h>     // strcmp, strncmp
#include <stdio.h>      // snprintf

//=============================================================================
// Public Methods: execute()
// Description: Execute the PWM command using the PWM Hardware Interface.
// Restriction: Accessible in CommandParser Class Only
//=============================================================================
void PWMCommand::execute(const char* command) {
   // Continuously adjust LED brightness based on potentiometer value
    if (strcmp(command, "pwm led pot") == 0) {
        while (1) {
            // Get ADC value from potentiometer
            uint16_t adcValue = adc.readADC(POT_ADC_CHANNEL);

            // Map ADC value (0-1023) to duty cycle (0-255)
            uint8_t dutyCycle = static_cast<uint8_t>(
                map(adcValue, 0, 1023, 0, 255));

            pwm.setDutyCycle(dutyCycle);

            _delay_ms(30); // Short delay to debounce/read rate control

            // Exit the loop when pot is turned to 0
            if (adcValue == 0) {
                break; 
            }
        }
    }

    // Set LED brightness based on a command input
    if (strncmp(command, "pwm led ", 8) == 0) {
        // Variable for the substring following "pwm led"
        int level;
        // Ensure the conversion succeeds
        if (sscanf(command + 8, "%d", &level) == 1) { 

            // Check if the level is within the valid range
            if (level >= 0 && level <= 10) {
                uint8_t dutyCycle = static_cast<uint8_t>(
                    map(level, 0, 10, 0, 255));

                // Set the LED brightness
                pwm.setDutyCycle(dutyCycle);
            } else {
                return; // Invalid level
            }
        } else {
            return; // Parsing error
        }
    }

    // Set PWM output and read ADC input
    if (strncmp(command, "pwm adc ", 8) == 0) {
    uint16_t milliVolts;

        // Attempt to parse the millivolts value from the command
        if (sscanf(command + 8, "%d", &milliVolts) == 1) {

            // Validate the parsed value is within the expected range
            if (milliVolts >= 0 && milliVolts <= 5000) {

                // Convert milliVolts to duty cycle & set PWM output
                uint8_t dutyCycle = static_cast<uint8_t>(
                    map(milliVolts, 0, 5000, 0, 255));

                pwm.setDutyCycle(dutyCycle);

                // Loop to read ADC value every second and convert to milliVolt
                for (uint8_t i = 0; i < 10; i++) {
                    uint16_t adcValue = adc.readADC(PWM_ADC_CHANNEL);
                    uint16_t adcVoltage = map(adcValue, 0, 1023, 0, 5000);

                    char buffer[128];
                    snprintf(buffer, sizeof(buffer), 
                            "PWM Set Output: %dmV, ADC Read Input: %dmV\r\n", 
                            milliVolts, adcVoltage
                            );
                    serial.print(buffer);

                    _delay_ms(1000); // Wait 1 second until next reading
                }

            } else {
                serial.print("Invalid milliVolts, must be between 0mV and 5000mV\r\n");
            }
        } else {
            serial.print("Parsing error: Could not interpret the PWM voltage\r\n");
        }
    }

    // Set PWM output, lower it by 10% and auto-adjust the PWM voltage using ADC input
    if (strncmp(command, "pwm auto adc ", 13) == 0) {
        // TODO: Initialize in constructor
        // PwmAdcConverter pwmAdcConverter(adc, pwm);
        uint16_t milliVolts;

        // Attempt to parse the millivolts value from the command
        if (sscanf(command + 13, "%d", &milliVolts) == 1) {
            if (milliVolts >= 0 && milliVolts <= 5000) {

                // Lower the voltage by 10%
                uint16_t adjustedMilliVolts = milliVolts * 0.9;

                // Convert milliVolts to duty cycle & set PWM output
                uint8_t dutyCycle = static_cast<uint8_t>(
                    map(adjustedMilliVolts, 0, 5000, 0, 255));

                // Set PWM 10% lower than the desired milliVolts
                pwm.setDutyCycle(dutyCycle);

                // Read ADC value and convert to milliVolt
                for (int i = 0; i < 30; i++) {
                    _delay_ms(500); // // Allow time for PWM adjustment

                    uint16_t adcValue = adc.readADC(PWM_ADC_CHANNEL);
                    uint16_t adcVoltage = map(adcValue, 0, 1023, 0, 5000);

                    // Calculate error between desired and actual milliVolts
                    int error = milliVolts - adcVoltage;
                    pwm.adjustDutyCycle(error);

                    char buffer[128];
                    snprintf(buffer, sizeof(buffer), 
                            "PWM Set: %dmV, PWM Adjust: %dmV, ADC Read: %dmV, Correction: %dmV\r\n", 
                            milliVolts, adjustedMilliVolts, adcVoltage, error
                            );
                    serial.print(buffer);
                }

            } else {
                serial.print("Invalid milliVolts, must be between 0mV and 5000mV\r\n");
            }
        } else {
            serial.print("Parsing error: Could not interpret the PWM voltage\r\n");
        }
    }
}