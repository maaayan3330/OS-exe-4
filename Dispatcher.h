#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>

class Dispatcher {
private:
    std::vector<BoundedBuffer*>& producerQueues; // תורים פרטיים של היוצרים
    std::unordered_map<std::string, BoundedBuffer*> dispatchQueues; // מיפוי סוגים לתורי Dispatcher
    int numProducers;            // מספר היוצרים
    int doneCount;               // מספר היוצרים ששלחו DONE
    int currentProducer;         // אינדקס היוצר הנוכחי בסריקה
    std::mutex printMutex;       // מנעול להדפסות

public:
    // Constructor
    Dispatcher(std::vector<BoundedBuffer*>& producerQueues,
               BoundedBuffer& sportsQueue,
               BoundedBuffer& newsQueue,
               BoundedBuffer& weatherQueue,
               int numProducers);

    // Destructor
    ~Dispatcher() = default;

    // Dispatch messages
    void dispatch();
};

#endif // DISPATCHER_H
