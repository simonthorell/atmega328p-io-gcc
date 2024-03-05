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

void CommandParser::parseButtonCommand(const char* command) {
    /* TODO: Implement... */
    (void)command;
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