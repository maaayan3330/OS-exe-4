#include "ScreenManager.h"
#include <iostream>

// Constructor
ScreenManager::ScreenManager(BoundedBuffer& sharedQueue, int numEditors)
    : sharedQueue(sharedQueue), numEditors(numEditors), doneCount(0) {}

// Display function
void ScreenManager::display() {
    while (true) {
        // Get a message from the shared queue
        std::string message = sharedQueue.remove();

        // Check for DONE message
        if (message == "DONE") {
            doneCount++;
            std::cout << "Screen Manager received DONE (" << doneCount << "/" << numEditors << ").\n";

            // If all Co-Editors sent DONE, break
            if (doneCount == numEditors) {
                break;
            }
        } else {
            // Display the message
            std::cout << "Screen Manager displayed: " << message << "\n";
        }
    }

    std::cout << "Screen Manager: DONE\n";
}
