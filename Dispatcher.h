#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "BoundedBuffer.h"

class Dispatcher {
private:
    std::vector<BoundedBuffer*>& producerQueues; // תורים פרטיים של היוצרים
    std::unordered_map<std::string, BoundedBuffer*> dispatchQueues; // מפת סוגים לתורים
    int numProducers; // מספר היוצרים
    int doneCount; // מונה הודעות DONE שהתקבלו
    size_t currentProducer; // אינדקס היוצר הנוכחי ב-Round Robin

public:
    // Constructor
    Dispatcher(std::vector<BoundedBuffer*>& producerQueues, 
               BoundedBuffer& sportsQueue, 
               BoundedBuffer& newsQueue, 
               BoundedBuffer& weatherQueue, 
               int numProducers);

    // Start dispatching messages
    void dispatch();
};

#endif // DISPATCHER_H
