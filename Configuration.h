#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>

struct ProducerConfig {
    int numProducts;  // Number of products to produce
    int queueSize;    // Queue size for this producer
};

struct Configuration {
    std::vector<ProducerConfig> producers;  // Configuration for each producer
    int coEditorQueueSize;                  // Shared queue size for Co-Editors
};

// Function to parse the configuration file
Configuration parseConfigurationFile(const std::string& filename);

#endif // CONFIGURATION_H
