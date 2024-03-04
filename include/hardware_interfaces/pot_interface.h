#ifndef POT_INTERFACE_H
#define POT_INTERFACE_H

#include "pin_map.h" // Include pin mapping

class POTInterface {
public:
    // Constructor
    POTInterface();

    // Function to read the value of the potentiometer
    int readValue();
};

#endif // POT_INTERFACE_H