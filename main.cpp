#include "Producer.h"
#include "BoundedBuffer.h"
#include <thread>
#include <vector>
#include "Dispatcher.h"

int main() {
    const int bufferSize = 10;
    const int numProducers = 2;
    const int numProducts = 5;

    // יצירת תורים פרטיים ליוצרים
    std::vector<BoundedBuffer*> producerQueues;
    for (int i = 0; i < numProducers; ++i) {
        producerQueues.push_back(new BoundedBuffer(bufferSize));
    }

    // יצירת תורי Dispatcher
    BoundedBuffer sportsQueue(bufferSize);
    BoundedBuffer newsQueue(bufferSize);
    BoundedBuffer weatherQueue(bufferSize);

    // יצירת יוצרים
    std::vector<std::thread> producerThreads;
    for (int i = 0; i < numProducers; ++i) {
        producerThreads.emplace_back([&, i]() {
            Producer producer(i + 1, numProducts, *producerQueues[i]);
            producer.produce();
        });
    }

    // יצירת Dispatcher
    Dispatcher dispatcher(producerQueues, sportsQueue, newsQueue, weatherQueue, numProducers);
    std::thread dispatcherThread([&]() { dispatcher.dispatch(); });

    // סיום עבודת היוצרים
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // סיום עבודת ה-Dispatcher
    dispatcherThread.join();

    // ניקוי זיכרון
    for (auto& queue : producerQueues) {
        delete queue;
    }

    return 0;
}
