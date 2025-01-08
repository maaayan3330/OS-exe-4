#include "Dispatcher.h"
#include <iostream>
#include <cstring> // For strcmp

// Constructor
Dispatcher::Dispatcher(std::vector<BoundedBuffer*>& producerQueues, BoundedBuffer& sportsQueue, BoundedBuffer& newsQueue, BoundedBuffer& weatherQueue)
    : producerQueues(producerQueues),
      sportsQueue(sportsQueue),
      newsQueue(newsQueue),
      weatherQueue(weatherQueue) {}

// Function to dispatch messages
void Dispatcher::dispatch() {
    size_t numProducers = producerQueues.size();
    // Track when each producer is done
    std::vector<bool> producersDone(numProducers, false);
    size_t doneCount = 0;

    // Round Robin index
    size_t currentIndex = 0;

    while (doneCount < numProducers) {
        BoundedBuffer* currentQueue = producerQueues[currentIndex];
        char* message = currentQueue->remove();

        // Check for "DONE"
        if (std::strcmp(message, "DONE") == 0) {
            if (!producersDone[currentIndex]) {
                producersDone[currentIndex] = true;
                doneCount++;
            }
            // Clean up memory for "DONE" message
            delete[] message;
        } else {
            // Sort messages by type
            if (std::strstr(message, "SPORTS") != nullptr) {
                sportsQueue.insert(message);
            } else if (std::strstr(message, "NEWS") != nullptr) {
                newsQueue.insert(message);
            } else if (std::strstr(message, "WEATHER") != nullptr) {
                weatherQueue.insert(message);
            } else {
                // In case of unexpected message type
                std::cerr << "Unknown message type: " << message << std::endl;
                delete[] message; // Clean up unexpected message
            }
        }

        // Round Robin
        currentIndex = (currentIndex + 1) % numProducers;
    }

    // Signal done for all queues
    sportsQueue.insert(new char[5]{'D', 'O', 'N', 'E', '\0'});
    newsQueue.insert(new char[5]{'D', 'O', 'N', 'E', '\0'});
    weatherQueue.insert(new char[5]{'D', 'O', 'N', 'E', '\0'});
}
