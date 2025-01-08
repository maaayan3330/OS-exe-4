#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>

struct ProducerConfig {
    int id;          // מזהה המפיק
    int numMessages; // מספר ההודעות שהמפיק מייצר
    int queueSize;   // גודל התור של המפיק
};

class Configuration {
private:
    std::vector<ProducerConfig> producers; // רשימת המפיקים
    int coEditorQueueSize;                // גודל התור המשותף לעורכים

public:
    // Constructor: טוען את הקונפיגורציה מהקובץ
    Configuration(const std::string& fileName);

    // Getters
    const std::vector<ProducerConfig>& getProducers() const;
    int getCoEditorQueueSize() const;
};

#endif  // CONFIGURATION_H
