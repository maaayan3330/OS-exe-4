#ifndef COUNTINGSEMAPHORE_H
#define COUNTINGSEMAPHORE_H

#include <semaphore.h>
#include <pthread.h>

class CountingSemaphore {
private:
    int value;                // הערך הנוכחי של הסמפור
    pthread_mutex_t mutex;    // Mutex לנעילת גישה
    sem_t S1;                 // סמפור בינארי ראשון
    sem_t S2;                 // סמפור בינארי שני

public:
    // Constructor - מאתחל סמפור עם ערך התחלתי
    CountingSemaphore(int initialValue);

    // Destructor - משחרר משאבים
    ~CountingSemaphore();

    // Down - מקטין את ערך הסמפור, עוצר תהליכים אם אין משאבים
    void down();

    // Up - מעלה את ערך הסמפור, משחרר תהליכים אם יש צורך
    void up();
};

#endif // COUNTINGSEMAPHORE_H
