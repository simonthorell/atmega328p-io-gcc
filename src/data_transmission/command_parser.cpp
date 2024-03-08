//==============================================================================
// Command Parser Class Implementation
//==============================================================================
#include "data_transmission/command_parser.h"
#include "hardware_interfaces/adc_interface.h"
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

//==============================================================================
// Constructor
//==============================================================================
CommandParser::CommandParser(USART& serial, LEDInterface& led, 
                             ButtonInterface& button, ADCInterface& adc,
                             PWMInterface& pwm) 
    : serial(serial), led(led), button(button), adc(adc), pwm(pwm) {}

//==============================================================================
// Public Methods: parseCommand
// Description:    Parses a command string received over UART and 
//                 executes the corresponding command.
//==============================================================================
void CommandParser::parseCommand(const char* command) {
    if (strncmp(command, "led", 3) == 0) {
        this->parseLedCommand(command);
    }
    else if (strncmp(command, "button", 6) == 0) {
        this->parseButtonCommand(command);
    }
    else if (strncmp(command, "adc", 3) == 0) {
        this->parseAdcCommand(command);
    }
    else if (strncmp(command, "pwm", 3) == 0) {
        this->parsePwmCommand(command);
    }
    else if (strncmp(command, "help", 4) == 0) {
        this->printHelp();
    } else {
        this->printError("Unrecognized command");
    }
}

//==============================================================================
// Private Methods: parseLedCommand, parsePwmCommand, parseButtonCommand, 
//                  parsePotentiometerCommand
// Description:     Parses and executes the corresponding UART-command.
//==============================================================================
void CommandParser::parseLedCommand(const char* command) {
    if (strcmp(command, "led green on") == 0) {
        led.greenOn();
    } else if (strcmp(command, "led green off") == 0) {
        led.greenOff();
    } else if (strcmp(command, "led red on") == 0) {
        led.redOn();
    } else if (strcmp(command, "led red off") == 0) {
        led.redOff();
    } else if (strcmp(command, "led blue on") == 0) {
        led.blueOn();
    } else if (strcmp(command, "led blue off") == 0) {
        led.blueOff();
    } else if (strcmp(command, "led lightshow") == 0) {
        led.lightShow();
    }
}

void CommandParser::parsePwmCommand(const char* command) {
    // Continuously adjust LED brightness based on potentiometer value
    if (strcmp(command, "pwm led pot") == 0) {
        while (1) {
            // Get ADC value from potentiometer
            uint16_t adcValue = adc.readADC(POT_ADC_CHANNEL);

            // Map ADC value (0-1023) to duty cycle (0-255)
            uint8_t dutyCycle = static_cast<uint8_t>(
                map(adcValue, 0, 1023, 0, 255));

            // Set PWM duty cycle according to ADC value
            pwm.setDutyCycle(dutyCycle);

            _delay_ms(30); // Short delay to debounce/read rate control

            if (adcValue == 0) {
                break; // Exit the loop when pot is turned to 0
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
}

void CommandParser::parseButtonCommand(const char* command) {
    if (strcmp(command, "button timer interupt") == 0) {
        button.setInterruptType(TIMER_2_INTERUPT);
    }

    if (strcmp(command, "button pci interupt") == 0) {
        button.setInterruptType(PIN_CHANGE_INTERUPT);
    }

    if (strcmp(command, "button state") == 0) {
        unsigned char lastPrintedStates[BUTTONS_COUNT] = {0};

        // Set loop cancel condition at 35 presses/bounces
        uint8_t pressCounter = 35;

        while(1) {
        for (int i = 0; i < BUTTONS_COUNT; ++i) {
            if (button.buttonStates[i] != lastPrintedStates[i]) {
                // Update state and prepare for printing
                lastPrintedStates[i] = button.buttonStates[i];

                // Buffer for printing button index
                char indexBuffer[20];
                snprintf(indexBuffer, sizeof(indexBuffer), "Button %d State: ", i);

                // Binary state representation buffer
                char bitString[9]; // 8 bits + null terminator
                unsigned char state = button.buttonStates[i];
                for (int bit = 7; bit >= 0; --bit) {
                    bitString[7 - bit] = (state & (1 << bit)) ? '1' : '0';
                }
                bitString[8] = '\0'; // Ensure null-termination

                // Print button state
                serial.print(indexBuffer);
                serial.print(bitString);
                serial.print("\n");

                pressCounter--;

                // Exit loop after 50 button press changes
                if (pressCounter == 0) {
                    return; // Exit if condition met
                }
            }
        }
    }
    }
}

void CommandParser::parseAdcCommand(const char* command) {
    if (strcmp(command, "adc read pot") == 0) {
        char buffer[128];
        while (1) {
            // Read ADC value and convert to voltage
            uint16_t adcValue = adc.readADC(POT_ADC_CHANNEL);
            float voltage = adcValue * 5.0 / 1024.0; // Convert to voltage

            // Manually convert the voltage to a string
            int voltage_int = static_cast<int>(voltage);
            int voltage_frac = static_cast<int>((voltage - voltage_int) * 100);

            snprintf(buffer, sizeof(buffer), 
                     "ADC Value: %d, Voltage: %d.%02dV\r\n", 
                     adcValue, voltage_int, voltage_frac
                    );
            serial.print(buffer);

            _delay_ms(300); // Wait for 300 milliseconds

            if (voltage == 0) {
                // Exit when pot is turned to 0V
                return;
            }
        }
    }
}

//==============================================================================
// Private Methods: printHelp, printError
// Description:     Prints a help message or an error message over UART.
//==============================================================================
void CommandParser::printHelp() {
    Data data(serial);
    data.printCommands();
}

void CommandParser::printError(const char* message) {
    serial.print("Error: ");
    serial.print(message);
}