#include "CoEditor.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructor
CoEditor::CoEditor(BoundedBuffer& inputQueue, BoundedBuffer& sharedQueue, const std::string& type)
    : inputQueue(inputQueue), sharedQueue(sharedQueue), type(type) {}

// Edit function
void CoEditor::edit() {
    std::cout << "CoEditor for " << type << " started.\n";
    while (true) {
        std::string message = inputQueue.remove();

        if (message == "DONE") {
            sharedQueue.insert(message.c_str());
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sharedQueue.insert(message.c_str());
        std::cout << "Co-Editor for " << type << " edited and passed: " << message << "\n";
    }
}

