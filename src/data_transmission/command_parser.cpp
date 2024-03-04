//=============================================================================
// Class: Command Parser
// Description: Parses and executes commands from the serial monitor and
//              prints help and error messages.
//=============================================================================
#include "data_transmission/command_parser.h"
// Hardware Abstraction Layers
#include "hardware_interfaces/leds.h"
#include "hardware_interfaces/buttons.h"
#include "hardware_interfaces/potentiometers.h"

//=============================================================================
// Constructor
//=============================================================================
CommandParser::CommandParser() {
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
    /* TODO: Implement... */
}

void CommandParser::parseButtonCommand(const char* command) {
    /* TODO: Implement... */
}

void CommandParser::parsePotentiometerCommand(const char* command) {
    /* TODO: Implement... */
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
}