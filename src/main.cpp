//======================================================================
// Main Application
//======================================================================
#include <avr/io.h>        // AVR I/O
#include <avr/interrupt.h> // AVR Interrupts

// Include Application Header-files
#include "data_transmission/usart.h"
#include "data_transmission/command_parser.h"
#include "hardware_interfaces/led_interface.h"
#include "hardware_interfaces/button_interface.h"
#include "hardware_interfaces/adc_interface.h"

// Function Prototypes
void loop(USART &serial, CommandParser &commandParser);

//======================================================================
// Main Function (Setup)
//======================================================================
int main(void) {
    sei();         // Enable Global Interrupts
    USART serial;  // Init UART with default baud rate

    // Initialize Hardware
    LEDInterface     led;
    ButtonInterface  button(led);
    ADCInterface     adcInterface;

    // Initialize UART command parser
    CommandParser commandParser(serial, led, button, adcInterface);

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