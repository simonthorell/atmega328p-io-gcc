#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdint.h>
#include <string.h>

class CommandParser {
public:
    // Constructor
    CommandParser();

    // Parses a command string and executes the corresponding command
    void parseCommand(const char* command);

private:
    // Parses and executes an "led" command
    void parseLedCommand(const char* command);

    // Parses and executes a "button" command
    void parseButtonCommand(const char* command);

    // Parses and executes a "potentiometer" command
    void parsePotentiometerCommand(const char* command);

    // Prints a help message
    void printHelp();

    // Prints an error message
    void printError(const char* message);
};

#endif // COMMAND_PARSER_H