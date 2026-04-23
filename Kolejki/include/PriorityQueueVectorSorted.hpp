#ifndef PRIORITY_QUEUE_VECTOR_SORTED_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_HPP
#include "IQueue.hpp"
#include <vector>
#include <memory>
#include "sort/Timsort.hpp"
using namespace std;

template <typename T>
struct DataItem{
    T &val;
    unsigned int priority;

    bool operator<(DataItem &other) const{
        return this->priority > other.priority;
    }

    bool operator>(DataItem &other) const{
        return this->priority < other.priority;
    }
};

template <typename T>
class PriorityQueueVectorSorted:IQueue<T>{
    private:
    unique_ptr<vector<DataItem>> _dataVector;
    public:
    PriorityQueueVectorSorted(){
        this->_size=0;
        this->_dataVector = make_unique<vector<DataItem>>();
    }
    void push(T &item, unsigned long priority) override;
    T& peek() override;
    T& pop() override;
    ~PriorityQueueVectorSorted(){}
};




#endif