#ifndef IQUEUE_HPP
#define IQUEUE_HPP
template <typename T>
class IQueue {
    protected:
    unsigned int _size = 0;
    public:
    virtual void push(T item, unsigned int priority) = 0;
    virtual T peek() = 0;
    virtual T pop() = 0;
    bool isEmpty(){
        return _size == 0;
    }
    virtual ~IQueue() = default;
};

#endif