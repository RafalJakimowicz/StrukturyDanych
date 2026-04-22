#ifndef QUEUE_HPP
#define QUEUE_HPP
template <typename T>
class Queue {
    protected:
    unsigned long _size = 0;
    public:
    virtual void push(T &item, unsigned long priority) = 0;
    virtual T& peek() = 0;
    virtual T& pop() = 0;
    bool isEmpty(){
        return _size == 0;
    }
};

#endif