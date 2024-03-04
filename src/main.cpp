// Main application file
#include <avr/io.h>
#include <avr/pgmspace.h>
// USART Interface & Command Parser
#include "data_transmission/usart.h"
#include "data_transmission/command_parser.h"

void loop(USART &serial, CommandParser &commandParser);

int main(void) {
    // Init USART with default baud rate
    USART serial;
    serial.init();

    // Init USART command parser
    CommandParser commandParser;

    // Run the app loop
    loop(serial, commandParser);
    
    return 0;
}

void loop(USART &serial, CommandParser &commandParser) {
    char receivedCommand[USART_CMD_BUFFER]; // command buffer

    while (1) {
        serial.print("Type a command: ");
        serial.receiveString(receivedCommand, USART_CMD_BUFFER);
        
        // Process the received command
        commandParser.parseCommand(receivedCommand);

        // Echo back the received string for testing
        // serial.print("\r\nYou typed: ");
        // serial.print(receivedCommand);
        // serial.print("\r\n");
    }
}