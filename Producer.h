#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <string>
#include <unordered_map>
#include <vector>

class Producer {
private:
    int id;                             // Producer ID
    int numProducts;                    // Total number of products to produce
    BoundedBuffer& queue;               // Producer's private queue (shared with Dispatcher)
    std::unordered_map<std::string, int> typeCounters; // Keeps track of strings per type

    // List of possible message types
    std::vector<std::string> types = {"SPORTS", "NEWS", "WEATHER"};

public:
    // Constructor
    Producer(int id, int numProducts, BoundedBuffer& queue);

    // Destructor
    ~Producer() = default;

    // Produce messages
    void produce();
};

#endif // PRODUCER_H
