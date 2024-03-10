//======================================================================
// Buttons Interface Class Implementation
//======================================================================
#include "hardware_interfaces/button_interface.h"

#define TIMER_DEBOUNCE_BITMASK 0b00011111 // 5 consecutive reads = press
#define PCI_DEBOUNCE_BITMASK   0b00000001 // only need high/low = press

const unsigned char ButtonInterface::buttonBits[BUTTONS_COUNT] = {
    BUTTON_1_BIT, BUTTON_2_BIT, BUTTON_3_BIT // Mapped in mcu_mapping.h
};

// Variable to hold 8-bit state of all buttons
volatile unsigned char ButtonInterface::buttonStates[BUTTONS_COUNT] = {0};
volatile unsigned char ButtonInterface::lastButtonStates[BUTTONS_COUNT] = {0};

// Static instance for static ISR methods to access non-static methods
ButtonInterface* ButtonInterface::instance = nullptr;

// Option 1: Use timer for interrupt to check button states and debounce
ISR(TIMER2_OVF_vect) {
	if (ButtonInterface::instance != nullptr && 
        ButtonInterface::instance->interuptType == TIMER_2_INTERUPT) {
        ButtonInterface::instance->updateButtonStates();
    }
}

// Option 2: Use pin change interrupt to check button states and debounce
ISR(BUTTON_ISR_VECT) {
	if (ButtonInterface::instance != nullptr && 
        ButtonInterface::instance->interuptType == PIN_CHANGE_INTERUPT) {
        ButtonInterface::instance->updateButtonStates();
    }
}

//======================================================================
// Constructor
//======================================================================
ButtonInterface::ButtonInterface(LEDInterface& ledInterface) : LED(ledInterface) {
    for (int i = 0; i < BUTTONS_COUNT; ++i) {
        // Set the button pin as input by clearing the DDR bit
        BUTTONS_DDR &= ~(1 << buttonBits[i]);
        // Enable the pull-up resistor by setting the PORT bit
        BUTTONS_PORT |= (1 << buttonBits[i]);
    }

	// Enable pin change interrupt for buttons
    PCICR |= (1 << BUTTONS_PCICR_ENABLE_BIT);
    BUTTONS_PCMSK_REGISTER |= BUTTONS_PCMSK_ENABLE_BITS;

	// Static instance for static methods to access non-static methods
    instance = this;

	// Set the default button interupt type & debounce bitMask
	instance->interuptType = TIMER_2_INTERUPT;
	instance->debounceBitMask = TIMER_DEBOUNCE_BITMASK;
}

//======================================================================
// Public Method: setInterruptType()
// Description:   Setter method to set the button interupt type & 
//                corresponding debounce bitMask.
//======================================================================
void ButtonInterface::setInterruptType(ButtonInteruptType type) {
	if (type == TIMER_2_INTERUPT) {
		ButtonInterface::instance->interuptType = TIMER_2_INTERUPT;
		ButtonInterface::instance->debounceBitMask = TIMER_DEBOUNCE_BITMASK;
	} else if (type == PIN_CHANGE_INTERUPT) {
		ButtonInterface::instance->interuptType = PIN_CHANGE_INTERUPT;
		ButtonInterface::instance->debounceBitMask = PCI_DEBOUNCE_BITMASK;
	}
}

//======================================================================
// Public Method: updateButtonStatesISR()
// Description:   Static method that updates the button states in ISR
//======================================================================
void ButtonInterface::updateButtonStates() {
    if (ButtonInterface::instance) {
        for (int i = 0; i < BUTTONS_COUNT; ++i) {
            // Shift the current state to left to make room for the new state
            buttonStates[i] <<= 1;

            // Read the current button state and set the least significant bit
            if (ButtonInterface::instance->readButton(buttonBits[i])) {
                buttonStates[i] |= 0x01; // '1' bit for pressed state
            }

            // Debounce the current state
            ButtonStatus currentState = 
                ButtonInterface::instance->buttonDebounce(buttonStates[i]);

            // Detect transitions to pressed state
            bool buttonIsPressed =
                currentState == BUTTON_PRESSED && 
				// Check last state to avoid multiple actions/toggles
                ButtonInterface::instance->lastButtonStates[i] != BUTTON_PRESSED;
                
            if (buttonIsPressed) {
                ButtonInterface::instance->handleButtonAction(i);
            }

            // Update the last debounced state for the next cycle
            ButtonInterface::instance->lastButtonStates[i] = currentState;
        }
    }
}

//======================================================================
// Private Methods: readButton, buttonDebounce, handleButtonAction
// Description:     Reads the state of the button, debounces the input,
//                  and handles the button action.
//======================================================================
bool ButtonInterface::readButton(unsigned char buttonBit) {
    // Use the bit definitions from mcu_mapping.h (LED_GREEN_BIT, etc.)
    return !(BUTTONS_PIN & (1 << buttonBit));
}

ButtonStatus ButtonInterface::buttonDebounce(unsigned char btn) {
    // Set button press stable when X consecutive reads are the same
    unsigned char bitMask = debounceBitMask;

    // Check the state of the button and return button status
    if((btn & bitMask) == bitMask) return BUTTON_PRESSED;
    if((btn & bitMask) == 0)       return BUTTON_RELEASED;
    return  BUTTON_BOUNCING;
}

void ButtonInterface::handleButtonAction(int buttonIndex) {
    switch (buttonIndex) {
        case 0: LED.greenToggle(); break;
        case 1: LED.redToggle();   break;
        case 2: LED.blueToggle();  break;
        // Add pin mapping in 'mcu_mapping.h' for more buttons and logic here...
    }
}