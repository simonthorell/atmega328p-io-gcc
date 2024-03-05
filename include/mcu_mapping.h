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

// PWM Output Pin
#define PWM_OUTPUT_DDR  DDRD
#define PWM_OUTPUT_PORT PORTD
#define PWM_OUTPUT_BIT  PORTD3  // Arduino Digital Pin 3

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
// Button Interrupt definitions
#define BUTTON_ISR_VECT PCINT1_vect // Pin change interrupt vector (D8-D13)

//======================================================================
// ADC Configuration
//======================================================================

// ADC Start Conversion
#define ADC_START_CONVERSION() (ADCSRA |= (1 << ADSC))

// Check if ADC Conversion is Complete
#define ADC_IS_CONVERSION_COMPLETE() (!(ADCSRA & (1 << ADSC)))

// ADC Reference Voltage Configuration
#define ADC_REF_VOLTAGE_AVCC (1 << REFS0)

// ADC Prescaler (128) Configuration 
#define ADC_PRESCALER_128 ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

// Potentiometer ADC Channel
#define POTENTIOMETER_CHANNEL 0 // Arduino Analog Pin ADC0

// Convenient Macro for Configuring ADC with Reference Voltage and Channel
#define CONFIGURE_ADC_FOR_CHANNEL(channel) (ADMUX = ADC_REF_VOLTAGE_AVCC | (channel))

#endif // MCU_MAPPING_H