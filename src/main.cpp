//======================================================================
// Main Application
//======================================================================
#include <avr/io.h>        // AVR I/O
#include <avr/interrupt.h> // AVR Interrupts
#include <avr/pgmspace.h>  // AVR Program Space Utilities

#include "data_transmission/usart.h"
#include "data_transmission/command_parser.h"
#include "hardware_interfaces/led_interface.h"
#include "hardware_interfaces/button_interface.h"
#include "hardware_interfaces/pot_interface.h"

void loop(USART &serial, CommandParser &commandParser);

//======================================================================
// Main Function (Setup)
//======================================================================
int main(void) {
    // Enable Global Interrupts
    sei();

    // Init USART with default baud rate
    USART serial;
    serial.init();

    // Initialize Hardware Interfaces
    LEDInterface LED;
    ButtonInterface BTN(LED);

    // Init USART command parser
    CommandParser commandParser(LED, BTN);

    // Run the app loop
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