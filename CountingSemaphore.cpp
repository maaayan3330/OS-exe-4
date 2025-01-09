#include "CountingSemaphore.h"
#include <iostream>

CountingSemaphore::CountingSemaphore(int initialValue)
    : value(initialValue) {
    pthread_mutex_init(&mutex, nullptr);
    sem_init(&S1, 0, 1); // S1 מתחיל כזמין (binary semaphore)
    sem_init(&S2, 0, 0); // S2 חסום בהתחלה
}

CountingSemaphore::~CountingSemaphore() {
    pthread_mutex_destroy(&mutex);
    sem_destroy(&S1);
    sem_destroy(&S2);
}

void CountingSemaphore::down() {
    sem_wait(&S1);         // נועל את S1
    pthread_mutex_lock(&mutex);

    value--;
    if (value < 0) {
        pthread_mutex_unlock(&mutex);
        sem_post(&S1);     // משחרר את S1 כדי שתהליכים אחרים יוכלו להמתין
        sem_wait(&S2);     // תהליך זה ממתין להתעוררות
    } else {
        pthread_mutex_unlock(&mutex);
        sem_post(&S1);     // משחרר את S1
    }
}

void CountingSemaphore::up() {
    sem_wait(&S1);         // נועל את S1
    pthread_mutex_lock(&mutex);

    value++;
    if (value <= 0) {
        sem_post(&S2);     // מעיר תהליך אחד ממתין ב-S2
    }

    pthread_mutex_unlock(&mutex);
    sem_post(&S1);         // משחרר את S1
}
