#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <random>

class Producer {
private:
    // <i>: Producer's ID
    int id;                    
    // The number of products a producer makes is specified via its constructor
    int numMessages;          
    // his spesific queue  
    BoundedBuffer& queue;      
    // <type>: A random type chosen from SPORTS, NEWS, WEATHER  
    std::vector<std::string> types = {"SPORTS", "NEWS", "WEATHER"};  

    // Map to track the count of messages per type
    std::unordered_map<std::string, int> typeCounters;

public:
    // Constructor
    Producer(int producerId, int messages, BoundedBuffer& buffer);

    // Function to start producing messages
    void produce();
};

#endif  // PRODUCER_H
