#include "hardware_interfaces/led_interface.h"
#include "pin_map.h"

void LEDInterface::init() {
    // Set LED pins as output
    LEDS_DDR |= (1 << LED_GREEN_BIT) | (1 << LED_RED_BIT) | (1 << LED_BLUE_BIT);
}

void LEDInterface::greenOn() {
    LEDS_PORT |= (1 << LED_GREEN_BIT); // Turn on Green LED
}

void LEDInterface::greenOff() {
    LEDS_PORT &= ~(1 << LED_GREEN_BIT); // Turn off Green LED
}

void LEDInterface::redOn() {
    LEDS_PORT |= (1 << LED_RED_BIT); // Turn on Red LED
}

void LEDInterface::redOff() {
    LEDS_PORT &= ~(1 << LED_RED_BIT); // Turn off Red LED
}

void LEDInterface::blueOn() {
    LEDS_PORT |= (1 << LED_BLUE_BIT); // Turn on Blue LED
}

void LEDInterface::blueOff() {
    LEDS_PORT &= ~(1 << LED_BLUE_BIT); // Turn off Blue LED
}