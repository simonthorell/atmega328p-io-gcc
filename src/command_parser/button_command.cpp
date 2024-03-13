//=============================================================================
// ButtonCommand Class Implementation
//=============================================================================
#include "command_parser/button_command.h"
#include <stdio.h> // snprintf

//=============================================================================
// Public Methods: execute
// Description: Execute the Button command using the Button Hardware Interface.
// Restriction: Accessible in CommandParser Class Only
//=============================================================================
void ButtonCommand::execute(const char* command) {
    if (strcmp(command, "button timer interupt") == 0) {
        button.setInterruptType(TIMER_2_INTERUPT);
    }

    if (strcmp(command, "button pci interupt") == 0) {
        button.setInterruptType(PIN_CHANGE_INTERUPT);
    }

    if (strcmp(command, "button state") == 0) {
        printButtonState(this->button);
    }
}

//=============================================================================
// Private Methods: buttonState
// Description:     Prints the 8-bit state of a pushed button over serial.
//=============================================================================
void ButtonCommand::printButtonState(ButtonInterface& button) {
    unsigned char lastPrintedStates[BUTTONS_COUNT] = {0};

    // Set loop cancel condition after 35 presses/bounces
    uint8_t pressCounter = 35;

    while(1) {
        for (int i = 0; i < BUTTONS_COUNT; ++i) {
            if (button.buttonStates[i] != lastPrintedStates[i]) {
                // Update state and prepare for printing
                lastPrintedStates[i] = button.buttonStates[i];

                // Buffer for printing button index
                char indexBuffer[20];
                snprintf(indexBuffer, sizeof(indexBuffer), "Button %d State: ", i);

                // Binary state representation buffer
                char bitString[9]; // 8 bits + null terminator
                unsigned char state = button.buttonStates[i];
                for (int bit = 7; bit >= 0; --bit) {
                    bitString[7 - bit] = (state & (1 << bit)) ? '1' : '0';
                }
                bitString[8] = '\0'; // Ensure null-termination

                // Print button state
                serial.print(indexBuffer);
                serial.print(bitString);
                serial.print("\n");

                // Keep track of when to exit loop
                pressCounter--;
                if (pressCounter == 0) {
                    return;
                }
            }
        }
    }
}