#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <mutex>
#include <semaphore.h>

// this is the class for a structer - BoundedBuffer
class BoundedBuffer {
private:
    std::queue<char*> buffer;  
    // max size of the queue
    size_t capacity;    
    // the binary semaphore     
    std::mutex mutex;    
    // the semaphore that count how much items in the queue      
    std::counting_semaphore<> full;  
    // the semaphore that count how much free spaces in the queue 
    std::counting_semaphore<> empty; 

public:
    //Constructor that creates a new bounded buffer with size places to store objects.
    BoundedBuffer(int size);

    // Inserts a new object into the bounded buffer
    void insert(char* s);

    // Removes and returns the first object from the bounded buffer
    char* remove();
};

#endif  
