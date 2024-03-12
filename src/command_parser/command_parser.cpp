//==============================================================================
// Command Parser Class Implementation
//==============================================================================
#include "command_parser/command_parser.h"
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

//==============================================================================
// Constructor
//==============================================================================
CommandParser::CommandParser(USART& serial, LEDInterface& led, 
                             ButtonInterface& button, ADCInterface& adc,
                             PWMInterface& pwm) 
    : serial(serial), led(led), button(button), adc(adc), pwm(pwm)
{
}

//==============================================================================
// Public Methods: parseCommand
// Description:    Parses a command string received over UART and 
//                 calls the appropriate command class to execute the command.
//==============================================================================
void CommandParser::parseCommand(const char* command) {
    if (strncmp(command, "led", 3) == 0) {
        LEDCommand(led).execute(command);
    }
    else if (strncmp(command, "button", 6) == 0) {
        ButtonCommand(serial, button).execute(command);
    }
    else if (strncmp(command, "adc", 3) == 0) {
        ADCCommand(serial, adc).execute(command);
    }
    else if (strncmp(command, "pwm", 3) == 0) {
        PWMCommand(serial, adc, pwm).execute(command);
    }
    else if (strncmp(command, "help", 4) == 0) {
        this->printHelp();
    } else {
        this->printError("Unrecognized command");
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
    serial.print("\r\n");
}