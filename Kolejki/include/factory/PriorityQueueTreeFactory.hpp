#ifndef PRIORITY_QUEUE_TREE_FACTORY_HPP
#define PRIORITY_QUEUE_TREE_FACTORY_HPP
#include <memory>
#include "queue/IQueue.hpp"
#include "queue/PriorityQueueTree.hpp"
#include "IQueueFactory.hpp"
using namespace std;

template <typename T>
class PriorityQueueTreeFactory : public IQueueFactory<T>{
    public:
    unique_ptr<IQueue<T>> create(){
        return make_unique<PriorityQueueTree<T>>();
    };
};

#endif