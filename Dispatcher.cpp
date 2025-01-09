#include "Dispatcher.h"
#include <iostream>

// Constructor
Dispatcher::Dispatcher(std::vector<BoundedBuffer*>& producerQueues, 
                       BoundedBuffer& sportsQueue,
                       BoundedBuffer& newsQueue,
                       BoundedBuffer& weatherQueue,
                       int numProducers)
    : producerQueues(producerQueues), numProducers(numProducers), doneCount(0) {
    // Map types to their respective queues using pointers
    dispatchQueues["SPORTS"] = &sportsQueue;
    dispatchQueues["NEWS"] = &newsQueue;
    dispatchQueues["WEATHER"] = &weatherQueue;
}

// Dispatch function
void Dispatcher::dispatch() {
    size_t currentProducer = 0; // Start with the first producer

    while (doneCount < numProducers) {
        // Access the current producer's queue
        BoundedBuffer* currentQueue = producerQueues[currentProducer];

        // Try to remove a message from the current producer's queue
        std::string message = currentQueue->remove();

        std::cout << "Dispatcher processing message: " << message << " from Producer " << (currentProducer + 1) << "\n";

        if (message.find("DONE") != std::string::npos) {
            doneCount++;
            std::cout << "Dispatcher received DONE from Producer " << (currentProducer + 1) 
                      << " (" << doneCount << "/" << numProducers << ")\n";

            // Send DONE to all dispatch queues
            for (auto& [type, queue] : dispatchQueues) {
                queue->insert("DONE");
                std::cout << "Dispatcher sent DONE to " << type << " queue.\n";
            }
        } else {
            // Parse the message to find its type
            size_t typeStart = message.find(" ") + 1;
            typeStart = message.find(" ", typeStart) + 1;
            size_t typeEnd = message.find(" ", typeStart);
            std::string type = message.substr(typeStart, typeEnd - typeStart);

            // Send the message to the appropriate queue
            if (dispatchQueues.find(type) != dispatchQueues.end()) {
                dispatchQueues[type]->insert(message.c_str());
                std::cout << "Dispatcher sent: " << message << " to " << type << " queue.\n";
            }
        }

        // Move to the next producer in the Round Robin
        currentProducer = (currentProducer + 1) % producerQueues.size();
    }

    std::cout << "Dispatcher finished processing all messages.\n";
}
