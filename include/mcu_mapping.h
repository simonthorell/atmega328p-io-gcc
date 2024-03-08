#ifndef MCU_MAPPING_H
#define MCU_MAPPING_H

#include <avr/io.h>

//======================================================================
// USART Configuration
//======================================================================
#define F_CPU 16000000UL         // CPU frequency in Hz
#define BAUD 9600                // USART baud rate
#define MY_UBRR F_CPU/16/BAUD-1  // UBRR value for 9600 baud rate
#define USART_CMD_BUFFER 32      // USART command buffer size

//======================================================================
// PIN Definitions
//======================================================================

// DDR and PORT Definitions for LEDs (All on PORTD)
#define LEDS_DDR        DDRD
#define LEDS_PORT       PORTD
#define LED_GREEN_BIT   PORTD5  // Arduino Digital Pin 5
#define LED_RED_BIT     PORTD6  // Arduino Digital Pin 6
#define LED_BLUE_BIT    PORTD7  // Arduino Digital Pin 7

// DDR and PORT Definitions for Buttons (All on PORTB)
#define BUTTONS_DDR     DDRB
#define BUTTONS_PORT    PORTB
#define BUTTONS_PIN     PINB
#define BUTTON_1_BIT    PORTB1  // Arduino Digital Pin 9
#define BUTTON_2_BIT    PORTB2  // Arduino Digital Pin 10
#define BUTTON_3_BIT    PORTB3  // Arduino Digital Pin 11

// Button Pin Change Interrupt (PIC) vector (D8-D13)
#define BUTTON_ISR_VECT PCINT0_vect

// Button enum for easy indexing and state storage
typedef enum {
    BUTTON_1 = 0,
    BUTTON_2,
    BUTTON_3,
    BUTTONS_COUNT // Will give the amount of buttons
} ButtonIndex;

// Potentiometer ADC Channel
#define POT_ADC_CHANNEL 0 // Arduino Analog Pin ADC0

// PWM to ADC Channel (Use PWM from PIN D3 by disable LED on Pin D5)
#define PWM_ADC_CHANNEL 1 // Arduino Analog Pin ADC1

//======================================================================
// PWM Definitions
//======================================================================
// Define which pin is used for PWM to map correct registers
#define USING_PWM_PIN_3

// Definitions for PWM on Pin 3 using Timer 2 (8-bit)
#ifdef USING_PWM_PIN_3
    #define PWM_OUTPUT_DDR   DDRD
    #define PWM_OUTPUT_BIT   PORTD3
    #define PWM_OUTPUT_OC    OCR2B
    #define PWM_TCCRA        TCCR2A
    #define PWM_TCCRB        TCCR2B
    #define PWM_COMx1        COM2B1
    #define PWM_WGMx0        WGM20
    #define PWM_WGMx1        WGM21
    #define PWM_CSx1         CS21
// Example for 16-bit Timer 0 using Pin D5
#elif defined(USING_PWM_PIN_5) 
    #define PWM_OUTPUT_DDR   DDRD
    #define PWM_OUTPUT_BIT   PORTD5
    #define PWM_OUTPUT_OC    OCR0B
    #define PWM_TCCRA        TCCR0A
    #define PWM_TCCRB        TCCR0B
    #define PWM_COMx1        COM0B1
    #define PWM_WGMx0        WGM00
    #define PWM_WGMx1        WGM01
    #define PWM_CSx1         CS01
#endif

#endif // MCU_MAPPING_H