#include "ScreenManager.h"
#include <iostream>

// Constructor
ScreenManager::ScreenManager(BoundedBuffer& sharedQueue, int numEditors)
    : sharedQueue(sharedQueue), numEditors(numEditors), doneCount(0) {}

// Display function
void ScreenManager::display() {
    std::cout << "Screen Manager started.\n";
    while (true) {
        std::string message = sharedQueue.remove();
    
        if (message == "DONE") {
            doneCount++;
            std::cout << "Screen Manager received DONE (" << doneCount << "/" << numEditors << ").\n";

            if (doneCount == numEditors) {
                break;
            }
        } else {
            std::cout << "Screen Manager displayed: " << message << "\n";
        }
    }
    std::cout << "Screen Manager: DONE\n";
}
