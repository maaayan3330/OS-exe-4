#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"
#include <string>

class CoEditor {
private:
    std::string type;           // סוג העורך (SPORTS, NEWS, WEATHER)
    BoundedBuffer& inputQueue;  // תור ההודעות לעורך
    BoundedBuffer& outputQueue; // תור ההודעות המשותף עם מנהל המסך

public:
    // Constructor
    CoEditor(const std::string& type, BoundedBuffer& inputQueue, BoundedBuffer& outputQueue);

    // Function to start editing messages
    void edit();
};

#endif  // COEDITOR_H
