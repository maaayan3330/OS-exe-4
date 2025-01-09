#include "Dispatcher.h"
#include <iostream>
#include "Shared.h"

// Constructor
Dispatcher::Dispatcher(std::vector<BoundedBuffer*>& producerQueues,
                       BoundedBuffer& sportsQueue,
                       BoundedBuffer& newsQueue,
                       BoundedBuffer& weatherQueue,
                       int numProducers)
    : producerQueues(producerQueues),
      numProducers(numProducers),
      doneCount(0),
      currentProducer(0) {
    // Map סוגים לתורים המתאימים
    dispatchQueues["SPORTS"] = &sportsQueue;
    dispatchQueues["NEWS"] = &newsQueue;
    dispatchQueues["WEATHER"] = &weatherQueue;
}

// Dispatch function
void Dispatcher::dispatch() {
    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << "Dispatcher started.\n";
    }

    while (doneCount < numProducers) {
        // קבלת תור היוצר הנוכחי
        BoundedBuffer* currentQueue = producerQueues[currentProducer];

        // בדיקה אם התור ריק
        if (currentQueue->isEmpty()) {
            // מעבר ליצרן הבא ב-Round Robin
            currentProducer = (currentProducer + 1) % producerQueues.size();
            continue;
        }

        // הסרת פריט מהתור
        char* message = currentQueue->remove();

        {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "Dispatcher processing message: " << message
                      << " from Producer " << (currentProducer + 1) << "\n";
        }

        // אם ההודעה היא DONE
        if (std::string(message).find("DONE") != std::string::npos) {
            doneCount++;
            {
                std::lock_guard<std::mutex> lock(printMutex);
                std::cout << "Dispatcher received DONE from Producer " << (currentProducer + 1)
                          << " (" << doneCount << "/" << numProducers << ")\n";
            }
        } else {
            // חילוץ סוג ההודעה
            size_t typeStart = std::string(message).find(" ") + 1;
            size_t typeEnd = std::string(message).find(" ", typeStart);
            std::string type = std::string(message).substr(typeStart, typeEnd - typeStart);

            // הכנסה לתור המתאים
            if (dispatchQueues.find(type) != dispatchQueues.end()) {
                dispatchQueues[type]->insert(message);
                {
                    std::lock_guard<std::mutex> lock(printMutex);
                    std::cout << "Dispatcher sent: " << message << " to " << type << " queue.\n";
                }
            }
        }

        // מחזור Round Robin
        currentProducer = (currentProducer + 1) % producerQueues.size();
    }

    // אחרי שכל היוצרים סיימו, שולח DONE לכל תורי Dispatcher
    for (auto& [type, queue] : dispatchQueues) {
        queue->insert(const_cast<char*>("DONE"));
        {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "Dispatcher sent DONE to " << type << " queue.\n";
        }
    }

    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << "Dispatcher finished processing all messages.\n";
    }
}
