#ifndef SHARED_H
#define SHARED_H

#include <mutex>

// הצהרה על printMutex כמשתנה גלובלי
extern std::mutex printMutex;

#endif // SHARED_H
