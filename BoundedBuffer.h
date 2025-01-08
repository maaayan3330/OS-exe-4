#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <mutex>
#include <semaphore.h>

class BoundedBuffer {
private:
    std::queue<char*> buffer;  // תור שמחזיק את המידע
    size_t capacity;           // גודל מקסימלי של התור
    std::mutex mutex;          // סמפור בינארי שמגן על גישה לתור
    std::counting_semaphore<> full;  // סמפור שעוקב אחרי מספר הפריטים בתור
    std::counting_semaphore<> empty; // סמפור שעוקב אחרי המקומות הפנויים בתור

public:
    // Constructor: יוצר Bounded Buffer בגודל קבוע
    BoundedBuffer(int size);

    // Inserts a new object into the bounded buffer
    void insert(char* s);

    // Removes and returns the first object from the bounded buffer
    char* remove();
};

#endif  // BOUNDED_BUFFER_H
