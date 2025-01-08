#include "ScreenManager.h"
#include <iostream>

// Constructor
ScreenManager::ScreenManager(BoundedBuffer& sharedQueue)
    : sharedQueue(sharedQueue) {}

// Function to display messages on the screen
void ScreenManager::display() {
    int doneCount = 0; // Counter for "DONE" messages

    while (doneCount < 3) { // מחכים לשלוש הודעות "DONE"
        // Remove a message from the shared queue
        char* message = sharedQueue.remove();

        // Check if the message is "DONE"
        if (std::string(message) == "DONE") {
            doneCount++;
        } else {
            // Print the message to the screen
            std::cout << "Screen Manager: " << message << std::endl;
        }
    }

    // Print final "DONE" message
    std::cout << "Screen Manager: DONE" << std::endl;
}


