#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include <vector>
#include <string>

class Dispatcher {
private:
    // a list of the producers
    std::vector<BoundedBuffer*>& producerQueues; 
    // S dispatcher queue
    BoundedBuffer& sportsQueue;    
    // N dispatcher queue            
    BoundedBuffer& newsQueue;  
    // W dispatcher queue                 
    BoundedBuffer& weatherQueue;               

public:
    // Constructor
    Dispatcher(std::vector<BoundedBuffer*>& producerQueues, BoundedBuffer& sportsQueue, BoundedBuffer& newsQueue, BoundedBuffer& weatherQueue);

    // Function to start dispatching messages
    void dispatch();
};

#endif 