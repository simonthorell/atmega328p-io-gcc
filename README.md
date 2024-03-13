# ATmega328p Programming with AVR-GCC

This project demonstrates programming the ATmega328p microcontroller using C++, compiling with AVR-GCC, and flashing/monitoring with custom Bash scripts. It's designed to provide a straightforward way to develop and deploy code on the ATmega328p, with tools for easy UART communication monitoring.

Developed using the [AVR Development Template](https://github.com/simonthorell/avr-dev-template), checkout the README in this repo for a more detailed setup and usage guide.

## Prerequisites
Before you begin, ensure the following software is installed on your system:

- **Docker**: For container management and isolation with pre-configured Linux dev environment.
- **Visual Studio Code (VS Code)**: As the integrated development environment.
- **Dev Containers**: A VS Code extension to simplify the use of Docker containers.
- **avrdude**: For programming the microcontroller's memory.

## Basic Usage
Getting started with the ATmega328p microcontroller involves three primary steps: connecting the device to your computer, flashing the firmware, and monitoring UART communication. This enables you to deploy your code and interact with the microcontroller through UART commands.

### Step 1: Connect the Microcontroller
1. **Physical Connection**: Connect the ATmega328p MCU to one of your computer's USB ports.

### Step 2: Develop & Build
The development and build process involves utilizing Docker for a consistent development environment and using CMake for compiling the project. Follow these steps to set up your environment and build your project within Visual Studio Code.

#### **Start Docker Dev-Container**:
1. **Run Docker**: Make sure Docker is running on your computer.
2. **Open Command Palette**: In Visual Studio Code, press `F1` or `CMD+Shift+P` (macOS) / `Ctrl+Shift+P` (Windows/Linux) to open the Command Palette.
3. **Rebuild Container**: Type `Dev Containers: Rebuild and Reopen in Container` and select it. This action will start Docker, build your development container based on the configuration in the `.devcontainer` folder, and reopen your project inside this container. This ensures that your development environment is consistent and isolated.

#### **Build the Binary with CMake**:
1. **Access CMake Commands**: With your project open in the Dev Container, press `F7` or again open the Command Palette with `F1` / `CMD+Shift+P` / `Ctrl+Shift+P` and type `CMake: Build`.
2. **Initiate Build**: Select `CMake: Build` from the list to start the compilation process. CMake automates the configuration and generates the necessary build files, compiling your project into a binary.

This process encapsulates your development environment within a Docker container for a consistent development environment. It ensures that all dependencies are handled automatically, and your build environment is precisely configured as per the project's requirements.

### Step 3: Flash the Firmware
Due to limitations of a docker container getting access to your local computer's hardware, run the below in a terminal outside the development environment.

4. **Prepare for Flashing**: Before you can flash the microcontroller, make sure you have installed all necessary software, such as `avrdude`, which is essential for the flashing process. The installation instructions for `avrdude` can vary depending on your operating system.
   
5. **Flash the Device**: Navigate to your project's `script` directory in the terminal or command prompt. Use the provided script to flash your firmware onto the ATmega328p:
    ```bash
    ./flash-firmware.sh -p <YOUR-DEVICE-PORT>
    ```
   Replace `<YOUR-DEVICE-PORT>` with the specific port your microcontroller is connected to.

### Step 3: Monitor UART Communication
6. **Initiate Monitoring**: To observe and interact with the microcontroller's serial communication, execute the monitoring script found in the `script` folder. This will open a command prompt for UART communication.
    ```bash
    ./monitor-mcu.sh
    ```
   
7. **Use UART Commands**: With the monitoring script running, you can send commands to the microcontroller. Start by typing `help` in the command prompt. This will print a list of available UART commands that you can use to control or query the microcontroller.

## Contribution
Contributions are welcome. Please fork the repository, make your changes, and submit a pull request.

## License
Distributed under the MIT License. See `LICENSE` for more information.