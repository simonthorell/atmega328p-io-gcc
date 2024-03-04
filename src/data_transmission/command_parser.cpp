//======================================================================
// Command Parser Class Implementation
//======================================================================
#include "data_transmission/command_parser.h"

//======================================================================
// Constructor
//======================================================================
CommandParser::CommandParser(LEDInterface& LED) : LED(LED) {}

//======================================================================
// Public Methods: parseCommand
// Description:    Parses a command string received over UART and 
//                 executes the corresponding command.
//======================================================================
uint8_t CommandParser::parseCommand(const char* command) {
    if (strncmp(command, "led", 3) == 0) {
        this->parseLedCommand(command);
    }
    else if (strncmp(command, "button", 6) == 0) {
        this->parseButtonCommand(command);
    }
    else if (strncmp(command, "potentiometer", 13) == 0) {
        this->parsePotentiometerCommand(command);
    }
    else if (strncmp(command, "help", 4) == 0) {
        this->printHelp();
    }
    else if (strncmp(command, "exit", 4) == 0) {
        return 1;
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
        LED.greenOn();
    } else if (strcmp(command, "led green off") == 0) {
        LED.greenOff();
    } else if (strcmp(command, "led red on") == 0) {
        LED.redOn();
    } else if (strcmp(command, "led red off") == 0) {
        LED.redOff();
    } else if (strcmp(command, "led blue on") == 0) {
        LED.blueOn();
    } else if (strcmp(command, "led blue off") == 0) {
        LED.blueOff();
    } else if (strcmp(command, "led lightshow") == 0) {
        LED.lightShow();
    }
}

void CommandParser::parseButtonCommand(const char* command) {
    /* TODO: Implement... */
    (void)command;
}

void CommandParser::parsePotentiometerCommand(const char* command) {
    /* TODO: Implement... */
    (void)command;
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