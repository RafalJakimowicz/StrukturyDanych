#ifndef IQUEUE_HPP
#define IQUEUE_HPP
template <typename T>
class IQueue {
    protected:
    unsigned int _size = 0;
    public:
    virtual void push(T item, unsigned int priority) = 0;
    virtual void changePriority(T item, unsigned int new_priority) = 0;
    virtual T peek() const = 0;
    virtual T pop() = 0;
    bool isEmpty() const{
        return _size == 0;
    }
    unsigned int size() const{
        return this->_size;
    }
    virtual ~IQueue() = default;
};

#endif