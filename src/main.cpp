//======================================================================
// Main Application
//======================================================================
#include <avr/io.h>
#include <avr/pgmspace.h>
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
    // Init USART with default baud rate
    USART serial;
    serial.init();

    // Initialize Hardware Interfaces
    LEDInterface LED;
    ButtonInterface button(LED);

    // Init USART command parser
    CommandParser commandParser(LED);

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
        uint8_t parserStatus = commandParser.parseCommand(receivedCommand);

        if (parserStatus == 1) {
            serial.print("Exiting...\r\n");
            break;
        }

    }
}