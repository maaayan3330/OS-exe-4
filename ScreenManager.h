#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <string>

class ScreenManager {
private:
    BoundedBuffer& sharedQueue; // Queue shared with Co-Editors
    int numEditors;             // Number of Co-Editors (usually 3)
    int doneCount;              // Counter for DONE messages

public:
    // Constructor
    ScreenManager(BoundedBuffer& sharedQueue, int numEditors);

    // Function to display messages
    void display();
};

#endif // SCREENMANAGER_H
