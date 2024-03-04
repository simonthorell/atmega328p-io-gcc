//=============================================================================
// Class: Command Parser
// Description: Parses and executes commands from the serial monitor and
//              prints help and error messages.
//=============================================================================
#include "data_transmission/command_parser.h"

//=============================================================================
// Constructor
//=============================================================================
CommandParser::CommandParser(LEDInterface& LED) : LED(LED) {
    /* Empty Constructor for now */
}

//=============================================================================
// Public Methods: parseCommand
// Description: Parses a command string and executes the corresponding command
//=============================================================================
void CommandParser::parseCommand(const char* command) {
    // Check for "led" command
    if (strncmp(command, "led", 3) == 0) {
        this->parseLedCommand(command);
    }
    // Check for "button" command
    else if (strncmp(command, "button", 6) == 0) {
        this->parseButtonCommand(command);
    }
    // Check for "potentiometer" command
    else if (strncmp(command, "potentiometer", 13) == 0) {
        this->parsePotentiometerCommand(command);
    }
    // Check for "help" command
    else if (strncmp(command, "help", 4) == 0) {
        this->printHelp();
    }
    // Unrecognized command
    else {
        this->printError("Unrecognized command");
    }
}

//=============================================================================
// Private Methods: parseLedCommand, parseButtonCommand, parsePotentiometerCommand
// Description: Parses and executes the corresponding command
//=============================================================================
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

//=============================================================================
// Private Methods: printHelp, printError
// Description: Prints a help message or an error message
//=============================================================================
void CommandParser::printHelp() {
    /* TODO: Implement... */
}

void CommandParser::printError(const char* message) {
    /* TODO: Implement... */
    (void)message; 
}