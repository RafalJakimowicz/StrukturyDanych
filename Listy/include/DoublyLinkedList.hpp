#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

template <typename T>
struct Node {
    T value;
    Node<T> * prev;
    Node<T> * next;
};

template <typename T>
class DoublyLinkedList{
private:
    unsigned int size;
    Node<T> * head;
    Node<T> * tail;
public:
    DoublyLinkedList(){
        this->size {0};
    }

    

    T operator[](unsigned int index){

    };
};


#endif