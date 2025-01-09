#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"

class Producer {
public:
    Producer(int id, int num_products, BoundedBuffer& queue);
    void produce();

private:
    int id;
    int num_products;
    BoundedBuffer& queue;
};

#endif // PRODUCER_H
