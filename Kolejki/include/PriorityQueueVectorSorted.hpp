#ifndef PRIORITY_QUEUE_VECTOR_SORTED_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_HPP
#include "IQueue.hpp"
#include <vector>
#include <iterator>
#include <memory>
#include "sort/Timsort.hpp"
#include <stdexcept>
using namespace std;

template <typename T>
struct DataItem{
    T val;
    unsigned int priority;

    bool operator<(DataItem &other) const{
        return this->priority > other.priority;
    }

    bool operator>(DataItem &other) const{
        return this->priority < other.priority;
    }
};

template <typename T>
class PriorityQueueVectorSorted : public IQueue<T>{
    private:
    const unique_ptr<vector<DataItem<T>>> _dataVector;
    const unique_ptr<TimSort<DataItem<T>>> _tSort;
    public:
    PriorityQueueVectorSorted() :
    _dataVector(make_unique<vector<DataItem<T>>>()),
    _tSort(make_unique<TimSort<DataItem<T>>>()){
        this->_size = 0;
    }

    PriorityQueueVectorSorted(const PriorityQueueVectorSorted& other): 
    _dataVector(make_unique<vector<DataItem<T>>>()),
    _tSort(make_unique<TimSort<DataItem<T>>>()){
        this->_size = 0;
        for(DataItem<T> d : (*other._dataVector)){
            this->push(d.val, d.priority);
        }
    }
    void push(T item, unsigned int priority) override;
    T peek() override;
    T pop() override;
    ~PriorityQueueVectorSorted(){}
};

template <typename T>
void PriorityQueueVectorSorted<T>::push(T item, unsigned int priority){
    DataItem<T> nd;
    nd.val = item;
    nd.priority = priority;
    this->_dataVector->push_back(nd);
    this->_tSort->sort(_dataVector->begin(), _dataVector->end());
    this->_size++;
};

template <typename T>
T PriorityQueueVectorSorted<T>::peek(){
    if(this->_size == 0){
        throw std::out_of_range("Queue is empty!");
    }
    return (*this->_dataVector)[0].val;
}

template <typename T>
T PriorityQueueVectorSorted<T>::pop(){
    if(this->_size == 0){
        throw std::out_of_range("Queue is empty!");
    }
    T val = (*this->_dataVector)[0].val;
    for(unsigned int i = 0; i < (*this->_dataVector).size() - 1; i++){
        (*this->_dataVector)[i] = (*this->_dataVector)[i+1];
    }
    this->_size--;
    (*this->_dataVector).resize(this->_size);
    return val;
}


#endif