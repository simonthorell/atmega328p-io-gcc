#ifndef BUTTON_COMMAND_H
#define BUTTON_COMMAND_H

#include <string.h>
#include "data_transmission/usart.h"
#include "hardware_interfaces/button_interface.h"

class CommandParser; // Forward Declaration

class ButtonCommand {
    // Restrict Access to CommandParser
    friend class CommandParser;

public:
    // Constructor
    ButtonCommand(USART &serial, ButtonInterface& button) 
        : serial(serial), button(button) {}

    // Methods Accessible to CommandParser
    void execute(const char* command);

private:
    USART& serial;
    ButtonInterface& button;

    // Private Methods
    void printButtonState(ButtonInterface& button);
};

#endif // BUTTON_COMMAND_H