//======================================================================
// Buttons Interface Class Implementation
//======================================================================
#include "hardware_interfaces/button_interface.h"

// Button MCU register bits (mapped in mcu_mapping.h)
const unsigned char ButtonInterface::buttonBits[BUTTONS_COUNT] = {
    BUTTON_1_BIT, BUTTON_2_BIT, BUTTON_3_BIT
};

// Variable to hold 8-bit state of all buttons
volatile unsigned char ButtonInterface::buttonStates[BUTTONS_COUNT] = {0};

// Indicate if an action has been triggered (for 'button state' command)
volatile bool ButtonInterface::actionTriggered = false;

// Static instance for static ISR methods to access non-static methods
ButtonInterface* ButtonInterface::instance = nullptr;

//**********************************************************************
// Interupt Option 1: Timer 2 (8-bit) - Timer Overflow interupt.
// Description:       This interupt is using a bit mask to debounce the
//                    button that is checked against the button states
//                    every time the timer 2 overflows. This ensures that
//                    the button is stable for 5 consecutive reads before
//                    the button press is registered.
//**********************************************************************
#define TIMER_DEBOUNCE_BITMASK 0b00011111 // 5 consecutive reads = press

// This ISR will be called every time TIMER2_OVF_vect overflows
ISR(TIMER2_OVF_vect) {
	if (ButtonInterface::instance != nullptr && 
        ButtonInterface::instance->interuptType == TIMER_2_INTERUPT) {
        
        // Handle interupt (Will use button states for debouncing)
        ButtonInterface::instance->updateButtonStatesOnTimerOverflow();
    }
}

//**********************************************************************
// Interupt Option 2: Timer 1 (16-bit) - PCI (Pin Change Interupt).
// Description:       This interupt is using Timer 1 to debounce the
//                    button by checking the if debounce time has passed
//                    since the last button press. This method is not as
//                    reliable as the Timer 2 interupt, but it is a good
//                    alternative.
//**********************************************************************
#define PCI_DEBOUNCE_TIME 40 // ms debounce time for Pin Change Interupt

volatile unsigned long lastPressTime = 0; // Last button press time

// This ISR will be called every millisecond (millis timer)
ISR(TIMER1_OVF_vect) {
    TCNT1 = 0xFF06; // Reload timer
}

// This ISR will be called on any pin change (button press)
ISR(BUTTON_ISR_VECT) {
	if (ButtonInterface::instance != nullptr && 
        ButtonInterface::instance->interuptType == PIN_CHANGE_INTERUPT) {

        // Handle interupt and pass current time for debounce logic
        ButtonInterface::instance->updateButtonStatesOnPinChange(TCNT1);
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

	// Set the default button interupt type (Timer Overflow)
	instance->interuptType = TIMER_2_INTERUPT;
}

//======================================================================
// Public Method: setInterruptType()
// Description:   Setter method to set the button interupt type.
//======================================================================
void ButtonInterface::setInterruptType(ButtonInteruptType type) {
	if (type == TIMER_2_INTERUPT) {
		ButtonInterface::instance->interuptType = TIMER_2_INTERUPT;
	} else if (type == PIN_CHANGE_INTERUPT) {
		ButtonInterface::instance->interuptType = PIN_CHANGE_INTERUPT;
        lastPressTime = 0; // Reset last press time for new interupt type
	}
    // Reset the actionTriggered flag (used for the 'button state' command)
    actionTriggered = false;
}

//======================================================================
// Public Methods: updateButtonStatesOnTimerOverflow, 
//                 updateButtonStatesOnPinChange
// Description:    Depending on what interupt type has been set using 
//                 setInteruptType(), these static methods will be
//                 called from the ISR to update the button states and
//                 handle the button actions.
//======================================================================
// Interupt Option 1: Timer 2 (8-bit) - Timer Overflow interupt
void ButtonInterface::updateButtonStatesOnTimerOverflow() {
    for (int i = 0; i < BUTTONS_COUNT; ++i) {
        // Set the current state of the button
        ButtonInterface::instance->setButtonState(i);

        // Debounce the current state using bit mask comparison
        ButtonStatus currentState = 
            ButtonInterface::instance->buttonDebounce(buttonStates[i]);
        
        // Check if the button is pressed and that the state has changed
        if (currentState == BUTTON_PRESSED && currentState != buttonStates[i]) {
            ButtonInterface::instance->handleButtonAction(i);
        }
    }
}

// Interupt Option 2: Timer 1 (16-bit) - PCI (Pin Change Interupt)
void ButtonInterface::updateButtonStatesOnPinChange(unsigned long currentTime) {
    // Set the current state of the button (Only to print states to serial)
    for (int i = 0; i < BUTTONS_COUNT; ++i) {
        ButtonInterface::instance->setButtonState(i);
    }

    // Debounce the button press using the last press time comparison
    if ((currentTime - lastPressTime) > PCI_DEBOUNCE_TIME) {
        for (int i = 0; i < BUTTONS_COUNT; ++i) {

            // Handle interupt if any bit is '1' (button pressed)
            if (ButtonInterface::instance->readButton(buttonBits[i])) {
                ButtonInterface::instance->handleButtonAction(i);
            }
        }
    }

    // Update last press time for next button press
    lastPressTime = currentTime;
}

//======================================================================
// Private Methods: readButton, buttonDebounce, handleButtonAction
// Description:     Reads the state of the button, debounces the input,
//                  and handles the button action.
//======================================================================
bool ButtonInterface::readButton(unsigned char buttonBit) {
    // Button register bits as defined in 'mcu_mapping.h'
    return !(BUTTONS_PIN & (1 << buttonBit));
}

void ButtonInterface::setButtonState(int buttonIndex) {
    // Shift the current bits to the left to make room for the new state
    buttonStates[buttonIndex] <<= 1;

    // Read the current button state and set the least significant bit
    if (readButton(buttonBits[buttonIndex])) {
        // Set the least significant bit to '1' for pressed state
        buttonStates[buttonIndex] |= 0x01;
    }
}

void ButtonInterface::resetButtonStates() {
    for (int i = 0; i < BUTTONS_COUNT; ++i) {
        buttonStates[i] = 0; // Set all button states to '00000000'
    }
}

void ButtonInterface::handleButtonAction(int buttonIndex) {
    switch (buttonIndex) {
        case 0: LED.greenToggle(); break;
        case 1: LED.redToggle();   break;
        case 2: LED.blueToggle();  break;
    }

    // Only used for the 'button state' command in the CommandParser
    actionTriggered = true;

    // Reset the button states after handling the action
    resetButtonStates();
}

//======================================================================
// Private Method: buttonDebounce
// Description:    Debounces the button input using a bit mask to check
//                 if X consecutive reads are the same. This is only 
//                 used for the Timer 2 overflow interupt option.
//======================================================================
ButtonStatus ButtonInterface::buttonDebounce(unsigned char btn) {
    // Set button press stable when X consecutive reads are the same
    unsigned char bitMask = TIMER_DEBOUNCE_BITMASK;

    // Check the state of the button and return button status
    if((btn & bitMask) == bitMask) return BUTTON_PRESSED;
    if((btn & bitMask) == 0)       return BUTTON_RELEASED;
    return  BUTTON_BOUNCING;
}