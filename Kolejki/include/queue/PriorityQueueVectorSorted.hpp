#ifndef PRIORITY_QUEUE_VECTOR_SORTED_HPP
#define PRIORITY_QUEUE_VECTOR_SORTED_HPP
#include "IQueue.hpp"
#include <vector>
#include <iterator>
#include <memory>
#include <stdexcept>

template <typename T>
struct DataItem{
    T val;
    unsigned int priority;

    bool operator<(const DataItem &other) const{
        return this->priority > other.priority;
    }

    bool operator>(const DataItem &other) const{
        return this->priority < other.priority;
    }
};

template <typename T>
class PriorityQueueVectorSorted : public IQueue<T>{
    private:
    std::vector<DataItem<T>> _dataVector;
    void _swap(DataItem<T> &d1, DataItem<T> &d2);
    public:
    PriorityQueueVectorSorted(){
        this->_size = 0;
    }

    PriorityQueueVectorSorted(const PriorityQueueVectorSorted& other){
        this->_size = 0;
        for(DataItem<T> d : other._dataVector){
            this->push(d.val, d.priority);
        }
    }
    void push(T item, unsigned int priority) override;
    void changePriority(T item, unsigned int new_priority) override;
    T peek() const override;
    T pop() override;
    ~PriorityQueueVectorSorted(){}
};

template <typename T>
void PriorityQueueVectorSorted<T>::_swap(DataItem<T> &d1, DataItem<T> &d2){
    T tmpVal = d1.val;
    unsigned int tmpPriority = d1.priority;

    d1.val = d2.val;
    d1.priority = d2.priority;

    d2.val = tmpVal;
    d2.priority = tmpPriority;
}

template <typename T>
void PriorityQueueVectorSorted<T>::push(T item, unsigned int priority){
    DataItem<T> nd;
    nd.val = item;
    nd.priority = priority;
    this->_dataVector.push_back(nd);
    for(int i = this->_size; i > 0; i--){
        if(this->_dataVector[i].priority > this->_dataVector[i - 1].priority){
            this->_swap(this->_dataVector[i], this->_dataVector[i - 1]);
        }
        else{
            break;
        }
    }
    this->_size++;
};

template <typename T>
T PriorityQueueVectorSorted<T>::peek() const{
    if(this->_size == 0){
        throw std::out_of_range("Queue is empty!");
    }
    return this->_dataVector[0].val;
}

template <typename T>
void PriorityQueueVectorSorted<T>::changePriority(T item, unsigned int new_priority){
    if(this->_size == 0){
        throw std::runtime_error("Queue is empty");
    }

    for(int i = 0; i < this->_size; i++){
        if(this->_dataVector[i].val == item){

            unsigned int oldPriority = this->_dataVector[i].priority;
            this->_dataVector[i].priority = new_priority;

            if(new_priority > oldPriority){
                for(int j = i; j > 0; j--){
                    if(this->_dataVector[j].priority > this->_dataVector[j - 1].priority){
                        this->_swap(this->_dataVector[j], this->_dataVector[j - 1]);
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                for(int j = i; j < this->_size - 1; j++){
                    if(this->_dataVector[j].priority < this->_dataVector[j + 1].priority){
                        this->_swap(this->_dataVector[j], this->_dataVector[j + 1]);
                    }
                    else{
                        break;
                    }
                }
            }
            return;
        }
    }

    throw std::runtime_error("Item not found in queue");
}

template <typename T>
T PriorityQueueVectorSorted<T>::pop(){
    if(this->_size == 0){
        throw std::out_of_range("Queue is empty!");
    }
    T val = this->_dataVector[0].val;
    for(unsigned int i = 0; i < this->_dataVector.size() - 1; i++){
        this->_dataVector[i] = this->_dataVector[i+1];
    }
    this->_size--;
    this->_dataVector.resize(this->_size);
    return val;
}


#endif