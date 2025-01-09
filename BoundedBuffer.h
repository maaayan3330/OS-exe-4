#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <cstring> // For strdup and free

class BoundedBuffer {
private:
    std::queue<char*> buffer;
    int maxSize;

    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;

public:
    // Constructor
    BoundedBuffer(int size);

    // Destructor
    ~BoundedBuffer();

    // Insert into the buffer
    void insert(const char* item);

    // Remove from the buffer
    char* remove();
};

#endif // BOUNDED_BUFFER_H
