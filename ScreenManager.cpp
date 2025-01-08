#include "ScreenManager.h"
#include <iostream>
#include <cstring> // For strcmp

// Constructor
ScreenManager::ScreenManager(BoundedBuffer& sharedQueue)
    : sharedQueue(sharedQueue) {}

// Function to display messages on the screen
void ScreenManager::display() {
    int doneCount = 0; // Counter for "DONE" messages

    while (doneCount < 3) { // Wait for three "DONE" messages
        // Remove a message from the shared queue
        char* message = sharedQueue.remove();

        // Check if the message is "DONE"
        if (std::strcmp(message, "DONE") == 0) {
            doneCount++;
        } else {
            // Print the message to the screen
            std::cout << "Screen Manager: " << message << std::endl;
        }

        // Free the memory of the message
        delete[] message;
    }

    // Print final "DONE" message
    std::cout << "Screen Manager: DONE" << std::endl;
}
