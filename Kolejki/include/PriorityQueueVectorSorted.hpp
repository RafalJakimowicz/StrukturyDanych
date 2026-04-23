#ifndef PRIORITY_QUEUE_VECTOR_SORTED_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_HPP
#include "IQueue.hpp"
#include <vector>
#include <iterator>
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
    const unique_ptr<vector<DataItem>> _dataVector;
    const uniqui_ptr<TimSort<DataItem>> _tSort;
    public:
    PriorityQueueVectorSorted(){
        this->_size=0;
        this->_dataVector = make_unique<vector<DataItem>>();
        this->_tSort = make_unique<TimSort<DataItem>>();
    }
    void push(T &item, unsigned int priority) override;
    T& peek() override;
    T& pop() override;
    ~PriorityQueueVectorSorted(){}
};

template <typename T>
void PriorityQueueVectorSorted<T>::push(T &item, unsigned int priority){
    DataItem<T> nd;
    nd.val = item;
    nd.priority = priority;
    this->_dataVector->push_back(nd);
    this->_tSort->sort(_dataVector->begin(), _dataVector->end());
    this->_size++;
};

template <typename T>
T &PriorityQueueVectorSorted<T>::peek(){
    if(this->_size == 0){
        return null;
    }
    return (*this->_dataVector)[0];
}

template <typename T>
T &PriorityQueueVectorSorted<T>::pop(){
    if(this->_size == 0){
        return null;
    }
    T val = (*this->_dataVector)[0];
    for(unsigned int i = 0; i < (*this->_dataVector).size(); i++){
        (*this->_dataVector)[i] = (*this->_dataVector)[i+1];
    }
    this->_size--;
    (*this->_dataVector).resize(this->_size);
    return val;
}


#endif