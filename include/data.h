#ifndef DATA_H
#define DATA_H

// USART for serial communication
#include "data_transmission/usart.h" 

class Data {
public:
    // Constructor
    Data(USART& serial); 

    // Method to print all commands
    void printCommands() const;

private:
    // Reference to the USART object
    USART& serial;
};

#endif // DATA_H