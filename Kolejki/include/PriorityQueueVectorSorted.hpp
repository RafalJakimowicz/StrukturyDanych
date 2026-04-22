#ifndef PRIORITY_QUEUE_VECTOR_SORTED_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_HPP
#include "IQueue.hpp"
#include <vector>

template <typename T>
struct DataItem{
    T &val;
    unsigned long priority;
};

template <typename T>
class PriorityQueueVectorSorted:IQueue<T>{
    private:
    std::vector<DataItem> _dataVector;
    public:
    PriorityQueueTree(){
        this->_size=0;
    }
    void push(T &item, unsigned long priority) override;
    T& peek() override;
    T& pop() override;
};


#endif