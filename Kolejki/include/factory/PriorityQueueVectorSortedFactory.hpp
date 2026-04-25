#ifndef PRIORITY_QUEUE_VECTOR_SORTED_FACTORY_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_FACTORY_HPP
#include <memory>
#include "queue/IQueue.hpp"
#include "queue/PriorityQueueVectorSorted.hpp"
#include "IQueueFactory.hpp"

template <typename T>
class PriorityQueueVectorSortedFactory : public IQueueFactory<T>{
    public:
    std::unique_ptr<IQueue<T>> create(){
        return std::make_unique<PriorityQueueVectorSorted<T>>();
    };
};

#endif