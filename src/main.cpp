//======================================================================
// Main Application
//======================================================================
#include <avr/io.h>        // AVR I/O
#include <avr/interrupt.h> // AVR Interrupts
#include <avr/pgmspace.h>  // AVR Program Space Utilities

// Include Application Header-files
#include "data_transmission/usart.h"
#include "data_transmission/command_parser.h"
#include "hardware_interfaces/led_interface.h"
#include "hardware_interfaces/button_interface.h"
#include "hardware_interfaces/pot_interface.h"

// Function Prototypes
void loop(USART &serial, CommandParser &commandParser);

//======================================================================
// Main Function (Setup)
//======================================================================
int main(void) {
    sei();          // Enable Global Interrupts
    USART serial;   // Init USART (UART only) with default baud rate

    // Initialize Hardware
    LEDInterface LED;
    ButtonInterface BTN(LED);
    POTInterface POT;

    // Initialize UART command parser
    CommandParser commandParser(LED, BTN, POT);

    // Run the application loop
    loop(serial, commandParser);
    
    return 0;
}

//======================================================================
// Main Loop
//======================================================================
void loop(USART &serial, CommandParser &commandParser) {
    char receivedCommand[USART_CMD_BUFFER]; // command buffer

    while (1) {
        serial.print("Type a command: ");
        serial.receiveString(receivedCommand, USART_CMD_BUFFER);
        
        // Process the received command
        commandParser.parseCommand(receivedCommand);
    }
}