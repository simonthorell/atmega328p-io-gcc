#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <avr/io.h>

// DDR and PORT Definitions for LEDs (All on PORTD)
#define LEDS_DDR        DDRD
#define LEDS_PORT       PORTD
#define LED_GREEN_BIT   PORTD5 // Arduino Digital Pin 5
#define LED_RED_BIT     PORTD6 // Arduino Digital Pin 6
#define LED_BLUE_BIT    PORTD7 // Arduino Digital Pin 7

// DDR and PORT Definitions for Buttons (All on PORTB)
#define BUTTONS_DDR     DDRB
#define BUTTONS_PORT    PORTB
#define BUTTONS_PIN     PINB
#define BUTTON_1_BIT    PORTB1 // Arduino Digital Pin 9
#define BUTTON_2_BIT    PORTB2 // Arduino Digital Pin 10
#define BUTTON_3_BIT    PORTB3 // Arduino Digital Pin 11

// PWM Output Pin
#define PWM_OUTPUT_DDR  DDRD
#define PWM_OUTPUT_PORT PORTD
#define PWM_OUTPUT_BIT  PORTD3 // Arduino Digital Pin 3

// Potentiometer ADC Channel
#define POTENTIOMETER_CHANNEL 0 // Arduino Analog Pin ADC0

#endif