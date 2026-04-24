#ifndef PRIORITY_QUEUE_VECTOR_SORTED_FACTORY_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_FACTORY_HPP
#include <memory>
#include "queue/IQueue.hpp"
#include "queue/PriorityQueueVectorSorted.hpp"
#include "IQueueFactory.hpp"
using namespace std;

template <typename T>
class PriorityQueueVectorSortedFactory : public IQueueFactory<T>{
    public:
    unique_ptr<IQueue<T>> create(){
        return make_unique<PriorityQueueVectorSorted<T>>();
    };
};

#endif