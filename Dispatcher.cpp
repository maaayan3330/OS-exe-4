#include "Dispatcher.h"
#include <iostream>

// Constructor
Dispatcher::Dispatcher(std::vector<BoundedBuffer*>& producerQueues, BoundedBuffer& sportsQueue, BoundedBuffer& newsQueue, BoundedBuffer& weatherQueue)
    : producerQueues(producerQueues),
      sportsQueue(sportsQueue),
      newsQueue(newsQueue),
      weatherQueue(weatherQueue) {}

// Function to dispatch messages
void Dispatcher::dispatch() {
    size_t numProducers = producerQueues.size();
    // keep an eye when the producer finish
    std::vector<bool> producersDone(numProducers, false); 
    // count how much producers finish
    size_t doneCount = 0; 

    // robin 
    size_t currentIndex = 0; 

    while (doneCount < numProducers) {
        BoundedBuffer* currentQueue = producerQueues[currentIndex];
        char* message = currentQueue->remove();

        // "DONE" - check 
        if (std::string(message) == "DONE") {
            if (!producersDone[currentIndex]) {
                producersDone[currentIndex] = true;
                doneCount++;
            }
        } else {
            // sort by type
            std::string msgString(message);
            if (msgString.find("SPORTS") != std::string::npos) {
                sportsQueue.insert(message);
            } else if (msgString.find("NEWS") != std::string::npos) {
                newsQueue.insert(message);
            } else if (msgString.find("WEATHER") != std::string::npos) {
                weatherQueue.insert(message);
            }
        }

        // Round Robin
        currentIndex = (currentIndex + 1) % numProducers;
    }

    // send done after all 
    sportsQueue.insert(const_cast<char*>("DONE"));
    newsQueue.insert(const_cast<char*>("DONE"));
    weatherQueue.insert(const_cast<char*>("DONE"));
}
