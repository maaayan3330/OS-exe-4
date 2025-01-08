#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBuffer {
private:
    std::queue<char*> buffer;       // התור המוגבל
    size_t capacity;                // הקיבולת המרבית של התור
    std::mutex mutex;               // מנעול לסנכרון גישה
    std::condition_variable not_full;  // אות למצב שהתור לא מלא
    std::condition_variable not_empty; // אות למצב שהתור לא ריק

public:
    // Constructor that creates a new bounded buffer with size places to store objects
    BoundedBuffer(int size);

    // Inserts a new object into the bounded buffer
    void insert(char* s);

    // Removes and returns the first object from the bounded buffer
    char* remove();
};

#endif
