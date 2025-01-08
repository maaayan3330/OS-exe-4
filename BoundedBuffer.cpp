#include "BoundedBuffer.h"

// Constructor
BoundedBuffer::BoundedBuffer(int size) : capacity(size) {}

// Inserts a new object into the bounded buffer
void BoundedBuffer::insert(char* s) {
    std::unique_lock<std::mutex> lock(mutex);

    // מחכים שהתור לא יהיה מלא
    not_full.wait(lock, [this]() { return buffer.size() < capacity; });

    // מוסיפים את הפריט לתור
    buffer.push(s);

    // מעירים את מי שמחכה שהתור לא יהיה ריק
    not_empty.notify_one();
}

// Removes and returns the first object from the bounded buffer
char* BoundedBuffer::remove() {
    std::unique_lock<std::mutex> lock(mutex);

    // מחכים שהתור לא יהיה ריק
    not_empty.wait(lock, [this]() { return !buffer.empty(); });

    // מוציאים את הפריט הראשון בתור
    char* item = buffer.front();
    buffer.pop();

    // מעירים את מי שמחכה שהתור לא יהיה מלא
    not_full.notify_one();

    // מחזירים את הפריט
    return item;
}
