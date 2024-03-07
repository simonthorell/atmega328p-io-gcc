//==============================================================================
// Data Class Implementation
// Description: Demonstrates how to save SRAM by storing strings in
//              flash memory (PROGMEM) and printing them over UART. 
//              This technique is useful even though we only use < 1kb of memory,
//              as SRAM is a limited resource on microcontrollers.
//==============================================================================
#include "data.h"
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#define PROGMEM_BUFFER_SIZE 64 // Adjust based on the longest string

// Define command strings in program memory (PROGMEM)
const char cmd1[] PROGMEM = "led green on";
const char cmd2[] PROGMEM = "led green off";
const char cmd3[] PROGMEM = "led red on";
const char cmd4[] PROGMEM = "led red off";
const char cmd5[] PROGMEM = "led blue on";
const char cmd6[] PROGMEM = "led blue off";
const char cmd7[] PROGMEM = "led lightshow (Random LED lightshow for 100 LED cycles)";
const char cmd8[] PROGMEM = "button timer interupt (Use Timer 2 for Button interupts)";
const char cmd9[] PROGMEM = "button pci interupt (Use Button Pin Change Interupts)";
const char cmd10[] PROGMEM = "button state (Prints 8-bit state for 35 button presses/bounces)";
const char cmd11[] PROGMEM = "adc read pot (Print POT value from ADC0 - turn to 0 to exit)";
const char cmd12[] PROGMEM = "pwm led pot (POT to adjust LED brightness - turn to 0 to exit)";
const char cmd13[] PROGMEM = "pwm led [0-10] (Set LED brightness between 0 and 10)";
const char cmd14[] PROGMEM = "help";

// Array of pointers to the command strings
const char* const commandStrings[] PROGMEM = {cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, 
                                              cmd7, cmd8, cmd9, cmd10, cmd11,
                                              cmd12, cmd13, cmd14};

//==============================================================================
// Constructor
//==============================================================================
Data::Data(USART& serial) : serial(serial) {}

//==============================================================================
// Public Methods: printCommands
// Description:    Prints all available commands over UART
//==============================================================================
void Data::printCommands() const {
    char buffer[PROGMEM_BUFFER_SIZE]; // Adjust based on the longest string
    // Loop through the command strings
    for (unsigned int i = 0; i < sizeof(commandStrings) / sizeof(commandStrings[0]); i++) {
        // Print a prefix before each command (For serial styling only)
        serial.print("  -");

        // Read the string from program memory then print it
        strcpy_P(buffer, (const char*)pgm_read_word(&(commandStrings[i])));
        serial.print(buffer);
        serial.print("\n"); // Print a newline after each command
    }
}