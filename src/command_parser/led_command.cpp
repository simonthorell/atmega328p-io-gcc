//=============================================================================
// LEDCommand Class Implementation
//=============================================================================
#include "command_parser/led_command.h"

//=============================================================================
// Public Methods: execute
// Description: Execute the LED command using the LED Hardware Interface.
// Restriction: Accessible in CommandParser Class Only
//=============================================================================
void LEDCommand::execute(const char* command) {
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