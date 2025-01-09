#include "Configuration.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Configuration parseConfigurationFile(const std::string& filename) {
    Configuration config;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open configuration file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRODUCER") != std::string::npos) {
            // Parse producer configuration
            ProducerConfig producer;
            if (!std::getline(file, line)) break;
            producer.numProducts = std::stoi(line);

            if (!std::getline(file, line)) break;
            auto pos = line.find("queue size = ");
            if (pos != std::string::npos) {
                producer.queueSize = std::stoi(line.substr(pos + 13));
            }

            config.producers.push_back(producer);
        } else if (line.find("Co-Editor queue size") != std::string::npos) {
            // Parse Co-Editor queue size
            auto pos = line.find("queue size = ");
            if (pos != std::string::npos) {
                config.coEditorQueueSize = std::stoi(line.substr(pos + 13));
            }
        }
    }

    file.close();
    return config;
}
