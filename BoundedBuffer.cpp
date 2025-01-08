#include "BoundedBuffer.h"

// Constructor
BoundedBuffer::BoundedBuffer(int size) 
    : capacity(size), full(0), empty(size) {}

// Inserts a new object into the bounded buffer
void BoundedBuffer::insert(char* s) {
    // down(empty) - go to slepp if there is no enoght place
    empty.acquire();  
    {
        // down(mutex)
        std::lock_guard<std::mutex> lock(mutex); 
        // add the string to the buffer
        buffer.push(s); 
    }
    // up(full)
    full.release();  
}

// Removes and returns the first object from the bounded buffer
char* BoundedBuffer::remove() {
    // down(full) - go to sleep is there no one to remove
    full.acquire();  
    char* item;
    {
        // down(mutex)
        std::lock_guard<std::mutex> lock(mutex); 
        // take the first item from queue
        item = buffer.front();  
        // take the elemnt off
        buffer.pop();           
    }
     // up(empty): - say there is hoe to take off 
    empty.release(); 
    // return the item that was took
    return item;  
}
