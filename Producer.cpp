#include "Producer.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructor
Producer::Producer(int producerId, int messages, BoundedBuffer& buffer)
    : id(producerId), numMessages(messages), queue(buffer) {
    // Initialize counters for each type to 0
    for (const auto& type : types) {
        typeCounters[type] = 0;
    }
}

// Function to produce messages
void Producer::produce() {
    // Random seed
    std::random_device rd;  
    // Random number generator
    std::mt19937 gen(rd()); 
    // For random message type
    std::uniform_int_distribution<> dis(0, types.size() - 1); 

    for (int i = 0; i < numMessages; ++i) {
        // Choose a random type
        std::string type = types[dis(gen)];

        // Get the current count for this type
        int count = typeCounters[type];

        // Create the message
        std::string message = "Producer " + std::to_string(id) + " " + type + " " + std::to_string(count);

        // Insert the message into the queue
        queue.insert(const_cast<char*>(message.c_str()));

        // Increment the counter for this type
        typeCounters[type]++;
    }

    // Signal that production is done
    queue.insert(const_cast<char*>("DONE"));
}
