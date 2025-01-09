#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include <string>
#include <vector>
#include <unordered_map>

class Dispatcher {
private:
    std::vector<BoundedBuffer*>& producerQueues;  // Queues shared with producers (Round Robin)
    std::unordered_map<std::string, BoundedBuffer*> dispatchQueues; // Queues per type (using pointers)
    int numProducers;              // Number of producers
    int doneCount;                 // Counter for DONE messages

public:
    // Constructor
    Dispatcher(std::vector<BoundedBuffer*>& producerQueues, 
               BoundedBuffer& sportsQueue,
               BoundedBuffer& newsQueue,
               BoundedBuffer& weatherQueue,
               int numProducers);

    // Function to start dispatching messages
    void dispatch();
};

#endif // DISPATCHER_H
