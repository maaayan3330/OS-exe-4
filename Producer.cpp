#include "Producer.h"
#include <iostream>
#include <cstdlib> // For rand()

// Constructor
Producer::Producer(int id, int numProducts, BoundedBuffer& queue)
    : id(id), numProducts(numProducts), queue(queue) {
    // Initialize type counters to zero
    for (const auto& type : types) {
        typeCounters[type] = 0;
    }
}

// Produce function
void Producer::produce() {
    std::cout << "Producer " << id << " started.\n";

    for (int i = 0; i < numProducts; ++i) {
        // Select a random type
        std::string type = types[rand() % types.size()];

        // Get the current count for this type
        int count = typeCounters[type]++;

        // Construct the message in the required format
        std::string message = "Producer " + std::to_string(id) + " " + type + " " + std::to_string(count);

        // Insert the message into the queue
        queue.insert(const_cast<char*>(message.c_str()));

        std::cout << "Producer " << id << " inserted: " << message << "\n";
    }

    // Send the DONE message
    std::string doneMessage = "Producer " + std::to_string(id) + " DONE";
    queue.insert(const_cast<char*>(doneMessage.c_str()));

    std::cout << "Producer " << id << " finished producing.\n";
}
