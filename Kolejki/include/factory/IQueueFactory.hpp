#ifndef IQUEUE_FACTORY_HPP
#define IQUEUE_FACTORY_HPP
#include <memory>
#include "queue/IQueue.hpp"
using namespace std;

template <typename T>
class IQueueFactory{
    public:
    virtual unique_ptr<IQueue<T>> create() = 0;
    virtual ~IQueueFactory() = default;
};

#endif