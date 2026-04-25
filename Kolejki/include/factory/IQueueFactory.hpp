#ifndef IQUEUE_FACTORY_HPP
#define IQUEUE_FACTORY_HPP
#include <memory>
#include "queue/IQueue.hpp"

template <typename T>
class IQueueFactory{
    public:
    virtual std::unique_ptr<IQueue<T>> create() = 0;
    virtual ~IQueueFactory() = default;
};

#endif