#include "CoEditor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring> // For strcmp

// Constructor
CoEditor::CoEditor(const std::string& type, BoundedBuffer& inputQueue, BoundedBuffer& outputQueue)
    : type(type), inputQueue(inputQueue), outputQueue(outputQueue) {}

// Function to edit messages
void CoEditor::edit() {
    while (true) {
        // Remove a message from the input queue
        char* message = inputQueue.remove();

        // Check for "DONE" message
        if (std::strcmp(message, "DONE") == 0) {
            // Forward "DONE" to the output queue
            outputQueue.insert(new char[5]{'D', 'O', 'N', 'E', '\0'});

            // Free the memory of the original "DONE" message
            delete[] message;

            // Exit the loop
            break;
        }

        // Simulate editing delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Forward the edited message to the output queue
        outputQueue.insert(message);
    }
}
