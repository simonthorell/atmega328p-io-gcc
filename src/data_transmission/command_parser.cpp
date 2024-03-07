//======================================================================
// Command Parser Class Implementation
//======================================================================
#include "data_transmission/command_parser.h"
#include "hardware_interfaces/adc_interface.h"
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

//======================================================================
// Constructor
//======================================================================
CommandParser::CommandParser(USART& serial, LEDInterface& led, 
                             ButtonInterface& button, ADCInterface& adcInterface) 
    : serial(serial), led(led), button(button), adcInterface(adcInterface) {
}

//======================================================================
// Public Methods: parseCommand
// Description:    Parses a command string received over UART and 
//                 executes the corresponding command.
//======================================================================
void CommandParser::parseCommand(const char* command) {
    if (strncmp(command, "led", 3) == 0) {
        this->parseLedCommand(command);
    }
    else if (strncmp(command, "button", 6) == 0) {
        this->parseButtonCommand(command);
    }
    else if (strncmp(command, "adc", 3) == 0) {
        this->parsePotentiometerCommand(command);
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

//======================================================================
// Private Methods: parseLedCommand, parseButtonCommand, 
//                  parsePotentiometerCommand
// Description:     Parses and executes the corresponding UART-command.
//======================================================================
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
    PWMInterface pwm;

    if (strcmp(command, "pwm led pot") == 0) {
       // Continuously adjust LED brightness based on potentiometer value
        while (1) {
            // Assuming adcInterface is an instance of AdcInterface and properly initialized
            uint16_t adcValue = adcInterface.Read(POT_ADC_CHANNEL);
            // Map ADC value (0-1023) to duty cycle (0-255)
            uint8_t dutyCycle = static_cast<uint8_t>(map(adcValue, 0, 1023, 0, 255));

            // Set PWM duty cycle according to ADC value
            pwm.setDutyCycle(dutyCycle);

            _delay_ms(30); // Short delay to debounce/read rate control

            if (adcValue == 0) {
                led.greenOff(); // Turn off LED
                break;          // Exit the loop when pot is turned to 0
            }
        }
    }

    if (strncmp(command, "pwm led ", 8) == 0) {
        // Extract the brightness level from the command
        int level = command[8] - '0'; // Convert the character to an integer

        // Check if the level is within the valid range
        if (level >= 0 && level <= 10) {
            // Map the level from 0-10 scale to 0-255 scale for PWM
            uint8_t dutyCycle = static_cast<uint8_t>(map(level, 0, 10, 0, 255));

            // Set the LED brightness
            pwm.setDutyCycle(dutyCycle);
        } else {
            // Invalid level
            return;
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

        uint8_t pressCounter = 50; // Number of presses before cancel the loop

        while(1) {
            for (int i = 0; i < BUTTONS_COUNT; ++i) {
                if (button.buttonStates[i] != lastPrintedStates[i]) {
                    // State has changed, update flag and last printed state
                    lastPrintedStates[i] = button.buttonStates[i];
                    
                    // Prepare to print button index
                    char indexBuffer[20]; // Ensure this buffer is large enough
                    snprintf(indexBuffer, sizeof(indexBuffer), "Button %d State: ", i);

                    // Generate bit string for new state
                    char bitString[9]; // Buffer for the binary representation + null terminator
                    unsigned char state = button.buttonStates[i];
                    for (int bit = 7; bit >= 0; --bit) {
                        bitString[7 - bit] = (state & (1 << bit)) ? '1' : '0';
                    }
                    bitString[8] = '\0'; // Null-terminate the string

                    // Print updated state with a label indicating the button index
                    serial.print(indexBuffer);
                    serial.print(bitString);
                    serial.print("\n");

                    pressCounter--;

                    if (pressCounter == 0) {
                        return; // Break the loop
                    }

                }
            }
        }
    }
}

void CommandParser::parsePotentiometerCommand(const char* command) {
    if (strcmp(command, "adc read pot") == 0) {
        char buffer[128];
        while (1) {
            // Read ADC value and convert to voltage
            uint16_t adcValue = adcInterface.Read(POT_ADC_CHANNEL);
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

//======================================================================
// Private Methods: printHelp, printError
// Description:     Prints a help message or an error message over UART.
//======================================================================
void CommandParser::printHelp() {
    /* TODO: Implement... */
}

void CommandParser::printError(const char* message) {
    /* TODO: Implement... */
    (void)message; 
}