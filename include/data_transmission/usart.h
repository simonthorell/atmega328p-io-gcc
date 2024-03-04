#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include "mcu_mapping.h"

class USART {
public:
    // Constructor
    USART(unsigned int ubrr = MY_UBRR);

    // Public Methods
    void transmit(unsigned char data);
    unsigned char receive();
    void print(const char* str);
    void receiveString(char* buffer, unsigned char max_length);
};

#endif // USART_H
