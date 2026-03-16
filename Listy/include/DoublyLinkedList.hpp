#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP
#include <stdexcept>

template <typename T>
struct Node {
    T val;
    Node<T> * prev;
    Node<T> * next;
};

template <typename T>
class DoublyLinkedList{
private:

    unsigned long _size;
    Node<T> * _head;
    Node<T> * _tail;

public:

    class Iterator{
        private:
        Node<T> * _current;
        public:
        Iterator(Node<T> * node) : _current(node){}
        
        T& operator*() {
            return this->_current->val;
        }
        
        Iterator& operator++(){
            if(this->_current != nullptr){
                this->_current = this->_current->next;
            }
            
            return *this;
        }
        
        Iterator& operator--(){
            if(this->_current != nullptr){
                this->_current = this->_current->prev;
            }
            
            return *this;
        }
        
        bool operator!=(const Iterator& other) const{
            return this->_current != other._current;
        }
        
        Node<T> * get(){
            return this->_current;
        }
    };

    Iterator begin(){
        return Iterator(this->_head);
    }

    Iterator end(){
        return Iterator(nullptr);
    }

private:

    Node<T> * _get(unsigned long index){
        if(index >= this->_size){
            throw std::runtime_error("Index out of range");
        }

        if(index < (_size / 2)){
            Iterator it = this->begin();
            for(unsigned long i = 0; i != index; i++){
                ++it;
            }
            return it.get();
        }
        else {
            Iterator it = Iterator(_tail);
            for(unsigned long i = this->_size - 1; i != index; i--){
                --it;
            }
            return it.get();
        }
    };

public:

    DoublyLinkedList(){
        this->_size = 0;
        this->_head = nullptr;
        this->_tail = nullptr;
    }

    //TODO konstruktor kopojacy i operator przypisania

    void append(T value){
        Node<T> * newNode = new Node<T>{value, nullptr, nullptr};

        if (this->_head == nullptr){
            this->_head = newNode;
            this->_tail = newNode;
        }
        else {
            newNode->prev = this->_tail;
            this->_tail->next = newNode;
            this->_tail = newNode;
        }

        this->_size++;
    };

    void remove(unsigned long index){
        if(index >= this->_size){
            throw std::runtime_error("Index out of range");
        }

        if(this->_size == 1){
            Node<T> * toRemove = this->_head;
            this->_head = nullptr;
            this->_tail = nullptr;
            delete toRemove;
        }
        else if(index + 1 == this->_size){
            Node<T> * toRemove = this->_tail;
            toRemove->prev->next = nullptr;
            this->_tail = toRemove->prev;
            delete toRemove;
        }
        else if(index == 0){
            Node<T> * toRemove = this->_head;
            toRemove->next->prev = nullptr;
            this->_head = toRemove->next;
            delete toRemove;
        }
        else{
            Node<T> * toRemove = this->_get(index);
            toRemove->prev->next = toRemove->next;
            toRemove->next->prev = toRemove->prev;
            delete toRemove;
        }
        this->_size--;
    };

    bool contains(T val){
        for(Iterator it = this->begin(); it != this->end(); ++it){
            if(*it == val){
                return true;
            }
        }
        return false;
    }

    void insert(T val, unsigned long index){
        Node<T> * newNode = new Node<T>{val, nullptr, nullptr};
        Node<T> * current = this->_get(index);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev = newNode;
    }

    void pop(){
        if(this->_size > 1){
            this->remove(this->_size - 1);
        }
        else{
            this->remove(0);
        }
    }

    T peek(){
        if(this->_size != 0){
            return this->_tail->val;
        }
        else{
            return nullptr;
        }
    }

    Iterator find(T val){
        for(Iterator it = this->begin(); it != this->end(); ++it){
            if(*it == val){
                return it;
            }
        }
        return this->end();
    }

    T& operator[](unsigned long index){
        return this->_get(index)->val;
    };

    unsigned long size(){
        return this->_size;
    };

    ~DoublyLinkedList(){
        while (this->_size > 0){
            this->remove(0);
        }
    }
};
#endif