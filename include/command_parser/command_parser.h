#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <string.h>

#include "data.h" // Data in PROGMEM
#include "data_transmission/usart.h" // Serial Communication

// Friend Classes
#include "command_parser/led_command.h"
#include "command_parser/button_command.h"
#include "command_parser/pwm_command.h"
#include "command_parser/adc_command.h"

class CommandParser {
public:
    // Constructor
    CommandParser(USART &serial,
                  LEDInterface &ledInterface,
                  ButtonInterface& buttonInterface,
                  ADCInterface& adcInterface,
                  PWMInterface& pwmInterface
                 );

    // Public Methods
    void parseCommand(const char* command);

private:
    // USART Interface Object
    USART& serial;

    // Hardware Interface Objects
    LEDInterface& led;
    ButtonInterface& button;
    ADCInterface& adc;
    PWMInterface& pwm;

    // Private Methods
    void printHelp();
    void printError(const char* message);
};

#endif // COMMAND_PARSER_H