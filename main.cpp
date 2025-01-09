#include "Producer.h"
#include "Dispatcher.h"
#include "BoundedBuffer.h"
#include <thread>
#include <vector>

int main() {
    const int bufferSize = 3;  // גודל התור
    const int numProducers = 2; // מספר היוצרים
    const int numProducts = 4;  // מספר המוצרים לכל יוצר

    // יצירת תורים פרטיים לכל יוצר
    std::vector<BoundedBuffer*> producerQueues;
    for (int i = 0; i < numProducers; ++i) {
        producerQueues.push_back(new BoundedBuffer(bufferSize));
    }

    // יצירת תורי Dispatcher
    BoundedBuffer sportsQueue(bufferSize);
    BoundedBuffer newsQueue(bufferSize);
    BoundedBuffer weatherQueue(bufferSize);

    // יצירת Producers
    std::vector<std::thread> producerThreads;
    for (int i = 0; i < numProducers; ++i) {
        producerThreads.emplace_back([&, i]() {
            Producer producer(i + 1, numProducts, *producerQueues[i]);
            producer.produce();
        });
    }

    // יצירת Dispatcher
    Dispatcher dispatcher(producerQueues, sportsQueue, newsQueue, weatherQueue, numProducers);
    std::thread dispatcherThread(&Dispatcher::dispatch, &dispatcher);

    // המתנה לכל היוצרים
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // המתנה ל-Dispatcher
    dispatcherThread.join();

    // ניקוי זיכרון
    for (auto& queue : producerQueues) {
        delete queue;
    }

    return 0;
}
