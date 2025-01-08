#include "Configuration.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Constructor: טוען את הקונפיגורציה מהקובץ
Configuration::Configuration(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + fileName);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRODUCER") != std::string::npos) {
            // קריאת מזהה המפיק
            int producerId = std::stoi(line.substr(9)); // "PRODUCER X"

            // קריאת מספר ההודעות
            std::getline(file, line);
            int numMessages = std::stoi(line);

            // קריאת גודל התור
            std::getline(file, line);
            int queueSize = std::stoi(line.substr(12)); // "queue size = X"

            producers.push_back({producerId, numMessages, queueSize});
        } else if (line.find("Co-Editor queue size") != std::string::npos) {
            // קריאת גודל התור של ה-Co-Editors
            coEditorQueueSize = std::stoi(line.substr(22)); // "Co-Editor queue size = X"
        }
    }
}

// Getters
const std::vector<ProducerConfig>& Configuration::getProducers() const {
    return producers;
}

int Configuration::getCoEditorQueueSize() const {
    return coEditorQueueSize;
}
