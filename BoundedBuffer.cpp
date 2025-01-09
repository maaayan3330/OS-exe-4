#include "BoundedBuffer.h"
#include <cstring>
#include <iostream>

// Constructor
BoundedBuffer::BoundedBuffer(int size)
    : maxSize(size), empty(size), full(0) {
    pthread_mutex_init(&mutex, nullptr);
}

// Destructor
BoundedBuffer::~BoundedBuffer() {
    pthread_mutex_destroy(&mutex);

    // מחיקת פריטים שנשארו בתור
    while (!buffer.empty()) {
        free(buffer.front());
        buffer.pop();
    }
}

// Insert into the buffer
void BoundedBuffer::insert(char* s) {
    char* copiedItem = strdup(s);    // יצירת עותק של המחרוזת
    empty.down();                   // המתנה למקום פנוי בתור
    pthread_mutex_lock(&mutex);     // נעילת התור

    buffer.push(copiedItem);        // הוספת הפריט לתור
    std::cout << "[Buffer Insert] Item inserted: " << copiedItem
              << ", Buffer size: " << buffer.size() << std::endl;

    pthread_mutex_unlock(&mutex);   // שחרור נעילת התור
    full.up();                      // עדכון שהתווסף פריט חדש
}

// Remove from the buffer
char* BoundedBuffer::remove() {
    full.down();                   // המתנה לפריט זמין בתור
    pthread_mutex_lock(&mutex);    // נעילת התור

    char* item = buffer.front();   // שליפת הפריט הראשון
    buffer.pop();                  // הסרת הפריט מהתור
    std::cout << "[Buffer Remove] Item removed: " << item
              << ", Buffer size: " << buffer.size() << std::endl;

    pthread_mutex_unlock(&mutex);  // שחרור נעילת התור
    empty.up();                    // עדכון שהתווסף מקום פנוי

    return item;                   // החזרת מצביע למחרוזת
}

bool BoundedBuffer::isEmpty() {
    pthread_mutex_lock(&mutex);
    bool empty = buffer.empty();
    pthread_mutex_unlock(&mutex);
    return empty;
}

