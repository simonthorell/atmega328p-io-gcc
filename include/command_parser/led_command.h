#ifndef LED_COMMAND_H
#define LED_COMMAND_H

#include <string.h>
#include "hardware_interfaces/led_interface.h"

class CommandParser; // Forward Declaration

class LEDCommand {
    // Restrict Access to CommandParser
    friend class CommandParser;

public:
    // Constructor
    LEDCommand(LEDInterface& led) : led(led) {}

    // Methods Accessible to CommandParser
    void execute(const char* command);

private:
    LEDInterface& led;
};

#endif // LED_COMMAND_H