#include "BoundedBuffer.h"
#include <iostream>

// Constructor
BoundedBuffer::BoundedBuffer(int size) : maxSize(size) {
    pthread_mutex_init(&mutex, nullptr);
    sem_init(&empty, 0, size); // Initially, buffer has 'size' empty slots
    sem_init(&full, 0, 0);     // Initially, buffer has no full slots
}

// Destructor
BoundedBuffer::~BoundedBuffer() {
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    // Free remaining items in the buffer
    while (!buffer.empty()) {
        free(buffer.front());
        buffer.pop();
    }
}

// Insert into the buffer
void BoundedBuffer::insert(const char* item) {
    char* copiedItem = strdup(item); // Duplicate the string
    sem_wait(&empty);               // Wait for an empty slot
    pthread_mutex_lock(&mutex);     // Lock the buffer

    buffer.push(copiedItem);
    std::cout << "Inserted: " << copiedItem << std::endl;

    pthread_mutex_unlock(&mutex);   // Unlock the buffer
    sem_post(&full);                // Signal that a slot is full
}

// Remove from the buffer
char* BoundedBuffer::remove() {
    sem_wait(&full);               // Wait for a full slot
    pthread_mutex_lock(&mutex);    // Lock the buffer

    char* item = buffer.front();
    buffer.pop();
    std::cout << "Removed: " << item << std::endl;

    pthread_mutex_unlock(&mutex);  // Unlock the buffer
    sem_post(&empty);              // Signal that a slot is empty

    return item; // Return the pointer to the item
}
