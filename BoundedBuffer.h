#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <queue>
#include <pthread.h>
#include "CountingSemaphore.h"

class BoundedBuffer {
private:
    std::queue<char*> buffer;       // תור לשמירת האובייקטים
    int maxSize;                    // הגודל המקסימלי של התור

    pthread_mutex_t mutex;          // מנעול לשמירה על גישה בטוחה לתור
    CountingSemaphore empty;        // סמפור המייצג מקומות פנויים בתור
    CountingSemaphore full;         // סמפור המייצג מקומות מלאים בתור

public:
    // Constructor
    BoundedBuffer(int size);

    // Destructor
    ~BoundedBuffer();

    // Insert into the buffer
    void insert(char* s);  // מחזירה void בהתאם לדרישה

    // Remove from the buffer
    char* remove();        // מחזירה מצביע למחרוזת

    bool isEmpty();

};

#endif // BOUNDED_BUFFER_H
