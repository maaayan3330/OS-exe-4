#include "CoEditor.h"
#include <iostream>
#include <thread> // For sleep
#include <chrono> // For time delays

// Constructor
CoEditor::CoEditor(BoundedBuffer& inputQueue, BoundedBuffer& sharedQueue, const std::string& type)
    : inputQueue(inputQueue), sharedQueue(sharedQueue), type(type) {}

// Edit function
void CoEditor::edit() {
    while (true) {
        // Get a message from the input queue
        std::string message = inputQueue.remove();

        // Check for DONE message
        if (message == "DONE") {
            std::cout << "Co-Editor for " << type << " received DONE. Passing it to Screen Manager.\n";
            sharedQueue.insert(message.c_str());
            break; // Stop editing when DONE is received
        }

        // Simulate editing by sleeping for 0.1 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Co-Editor for " << type << " edited: " << message << "\n";

        // Pass the message to the shared queue
        sharedQueue.insert(message.c_str());
    }

    std::cout << "Co-Editor for " << type << " finished processing messages.\n";
}
