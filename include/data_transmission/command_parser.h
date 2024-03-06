#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <string.h>

#include "data_transmission/usart.h"

// Hardware Abstraction Layers (Interfaces)
#include "hardware_interfaces/led_interface.h"
#include "hardware_interfaces/button_interface.h"
#include "hardware_interfaces/adc_interface.h"
#include "hardware_interfaces/pwm_interface.h"

class CommandParser {
public:
    // Constructor
    CommandParser(USART &serial,
                  LEDInterface &ledInterface,
                  ButtonInterface& buttonInterface,
                  ADCInterface& adcInterface
                 );

    // Public Methods
    void parseCommand(const char* command);

private:
    // USART Interface Object
    USART& serial;
    // Hardware Interface Objects
    LEDInterface& led;
    ButtonInterface& button;
    ADCInterface& adcInterface;

    // Private Methods
    void parseLedCommand(const char* command);
    void parsePwmCommand(const char* command);
    void parseButtonCommand(const char* command);
    void parsePotentiometerCommand(const char* command);
    void printHelp();
    void printError(const char* message);

    // Convert input value and scale it to a new range (ADC to PWM cycle)
    long map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
};

#endif // COMMAND_PARSER_H