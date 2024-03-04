#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <string.h>

// Hardware Abstraction Layers
#include "hardware_interfaces/led_interface.h"
#include "hardware_interfaces/button_interface.h"
#include "hardware_interfaces/pot_interface.h"

class CommandParser {
public:
    // Constructor
    CommandParser(LEDInterface &ledInterface);

    // Public Methods
    void parseCommand(const char* command);

private:
    // Hardware Interfaces
    LEDInterface& LED;

    // Private Methods
    void parseLedCommand(const char* command);
    void parseButtonCommand(const char* command);
    void parsePotentiometerCommand(const char* command);
    void printHelp();
    void printError(const char* message);
};

#endif // COMMAND_PARSER_H