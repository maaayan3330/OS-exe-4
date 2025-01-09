#include "Producer.h"
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <cstring>  // For strdup

Producer::Producer(int id, int num_products, BoundedBuffer &queue)
    : id(id), num_products(num_products), queue(queue) {}

void Producer::produce()
{
    std::vector<std::string> types = {"SPORTS", "NEWS", "WEATHER"};
    std::cout << "num_products: " << num_products << std::endl; // This should work now

    for (int i = 0; i < num_products; ++i)
    {
        std::string type = types[rand() % types.size()];
        // Convert std::string to const char* and insert it into the buffer
        std::string item = "Producer " + std::to_string(id) + " " + type + " " + std::to_string(i);
        queue.insert(strdup(item.c_str()));  // Use strdup to create a new char* copy
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "done " << num_products << std::endl; // This should work now

    queue.insert(strdup("DONE"));  // Send DONE message as a char*
}
