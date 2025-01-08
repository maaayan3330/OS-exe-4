#include "CoEditor.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructor
CoEditor::CoEditor(const std::string& type, BoundedBuffer& inputQueue, BoundedBuffer& outputQueue)
    : type(type), inputQueue(inputQueue), outputQueue(outputQueue) {}

// Function to edit messages
void CoEditor::edit() {
    while (true) {
        // Remove a message from the input queue
        char* message = inputQueue.remove();

        // Check for "DONE" message
        if (std::string(message) == "DONE") {
            // Forward "DONE" to the output queue and exit
            outputQueue.insert(const_cast<char*>("DONE"));
            break;
        }

        // Simulate editing delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Forward the edited message to the output queue
        outputQueue.insert(message);
    }
}
