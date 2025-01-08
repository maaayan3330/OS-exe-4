#include "BoundedBuffer.h"

// Constructor: יוצר Bounded Buffer בגודל קבוע
BoundedBuffer::BoundedBuffer(int size) 
    : capacity(size), full(0), empty(size) {}

// Inserts a new object into the bounded buffer
void BoundedBuffer::insert(char* s) {
    empty.acquire();  // down(empty): מחכה אם אין מקום פנוי בתור
    {
        std::lock_guard<std::mutex> lock(mutex); // down(mutex): נועל גישה לתור
        buffer.push(s);  // מוסיף את המחרוזת לתור
    }
    full.release();  // up(full): מסמן שיש פריט נוסף בתור
}

// Removes and returns the first object from the bounded buffer
char* BoundedBuffer::remove() {
    full.acquire();  // down(full): מחכה אם אין פריטים בתור
    char* item;
    {
        std::lock_guard<std::mutex> lock(mutex); // down(mutex): נועל גישה לתור
        item = buffer.front();  // לוקח את הפריט הראשון בתור
        buffer.pop();           // מסיר את הפריט מהתור
    }
    empty.release();  // up(empty): מסמן שיש מקום פנוי נוסף בתור
    return item;  // מחזיר את הפריט שהוסר
}
