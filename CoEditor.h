#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"
#include <string>

class CoEditor {
private:
    BoundedBuffer& inputQueue;  // Queue to receive messages from Dispatcher
    BoundedBuffer& sharedQueue; // Shared queue to send messages to Screen Manager
    std::string type;           // Type of Co-Editor (SPORTS, NEWS, WEATHER)

public:
    // Constructor
    CoEditor(BoundedBuffer& inputQueue, BoundedBuffer& sharedQueue, const std::string& type);

    // Function to start editing messages
    void edit();
};

#endif // COEDITOR_H
