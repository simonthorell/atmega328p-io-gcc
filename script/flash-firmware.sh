#!/bin/bash

# Define the default serial port to which the microcontroller is connected.
SERIAL_PORT=/dev/cu.usbserial-110

# Define the microcontroller type (e.g., ATmega328P).
MCU=atmega328p

# Define the programmer type (e.g., Arduino as ISP).
PROGRAMMER=arduino

# Define the path to the hex file you want to flash.
HEX_FILE=../build/avr-firmware.hex

# Check if avrdude is installed
if ! command -v avrdude &> /dev/null; then
    echo "avrdude is not installed."
    echo "To install avrdude, follow these instructions based on your operating system:"
    echo "macOS: Install Homebrew (https://brew.sh), then run 'brew install avrdude'"
    echo "Linux (Debian/Ubuntu): Run 'sudo apt-get update && sudo apt-get install avrdude'"
    echo "Windows: Download and install from http://www.nongnu.org/avrdude/"
    exit 1
fi

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -p|--port)
            SERIAL_PORT="$2"
            shift
            shift
            ;;
        *)
            # Unknown option
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Flash the microcontroller using avrdude.
avrdude -p $MCU -c $PROGRAMMER -P $SERIAL_PORT -U flash:w:$HEX_FILE:i

# Check if avrdude succeeded.
if [ $? -eq 0 ]; then
    echo "Flashing successful!"
else
    echo "Flashing failed."
fi