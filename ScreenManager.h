#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <string>

class ScreenManager {
private:
    BoundedBuffer& sharedQueue; // התור המשותף עם ה-Co-Editors

public:
    // Constructor
    ScreenManager(BoundedBuffer& sharedQueue);

    // Function to start managing the screen
    void display();
};

#endif  // SCREENMANAGER_H
