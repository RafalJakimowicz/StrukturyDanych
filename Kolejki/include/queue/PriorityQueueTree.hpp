#ifndef PRIORITY_QUEUE_TREE_HPP
#define PRIORITY_QUEUE_TREE_HPP
#include "IQueue.hpp"
#include <stdexcept>
#include <stack>

template <typename T>
struct TreeNode{
    TreeNode<T> * leftChild;
    TreeNode<T> * rightChild;
    TreeNode<T> * parent;
    T val;
    unsigned int priority;

    TreeNode(){
        this->leftChild = nullptr;
        this->parent = nullptr;
        this->rightChild = nullptr;
    }
};

template <typename T>
class PriorityQueueTree : public IQueue<T>{
    private:
    void _heapifyDown(TreeNode<T> * node);
    void _heapifyUp(TreeNode<T> * node);
    void _swap(TreeNode<T> * n1, TreeNode<T>* n2);
    void _copy_dfs(void (PriorityQueueTree<T>::*handler)(T, unsigned int), TreeNode<T> * current);
    TreeNode<T> * _search_dfs(T item, TreeNode<T> * current);
    TreeNode<T> * _root;
    public:
    PriorityQueueTree(){
        this->_root = nullptr;
        this->_size=0;
    }
    PriorityQueueTree(const PriorityQueueTree &other);
    void push(T item, unsigned int priority) override;
    T peek() const override;
    T pop() override;
    void changePriority(T item, unsigned int new_priority);
    ~PriorityQueueTree();
};

template <typename T>
TreeNode<T> * PriorityQueueTree<T>::_search_dfs(T item, TreeNode<T> * current){
    if(current == nullptr){
        return nullptr;
    }

    if(current->val == item){
        return current;
    }

    TreeNode<T> * result = this->_search_dfs(item, current->leftChild);
    
    if(result != nullptr){
        return result;
    }

    return this->_search_dfs(item, current->rightChild);
};

template <typename T>
void PriorityQueueTree<T>::changePriority(T item, unsigned int new_priority){
    TreeNode<T> * toChange = this->_search_dfs(item, this->_root);

    if(toChange == nullptr){
        throw std::runtime_error("Item not found in queue");
    }

    if(new_priority > toChange->priority){
        toChange->priority = new_priority;
        this->_heapifyUp(toChange);
    } 
    else {
        toChange->priority = new_priority;
        this->_heapifyDown(toChange);
    }
};

template <typename T>
PriorityQueueTree<T>::~PriorityQueueTree(){
    while(this->_size > 0){
        this->pop();
    }
};

template <typename T>
void PriorityQueueTree<T>::_copy_dfs(void (PriorityQueueTree<T>::*handler)(T, unsigned int), TreeNode<T> * current){
    if(current == nullptr){
        return;
    }

    (this->*handler)(current->val, current->priority);

    this->_copy_dfs(handler, current->leftChild);
    this->_copy_dfs(handler, current->rightChild);
};

template <typename T>
PriorityQueueTree<T>::PriorityQueueTree(const PriorityQueueTree &other){
    while(this->_size > 0){
        this->pop();
    }
    this->_root=nullptr;
    this->_copy_dfs(&PriorityQueueTree::push, other._root);
};

template <typename T>
void PriorityQueueTree<T>::push(T item, unsigned int priority){
    TreeNode<T> * newNode = new TreeNode<T>();
    newNode->val = item;
    newNode->priority = priority;
    this->_size++;
    if(this->_root == nullptr){
        this->_root = newNode;
        return;
    }

    std::stack<bool> directions;
    unsigned int tmp_size = this->_size;
    while(tmp_size > 0){
        directions.push((bool) (tmp_size & 1)); // tmp_size % 2
        tmp_size >>= 1; // tmp_size /= 2
    }
    directions.pop();
    TreeNode<T> * current = this->_root;
    while(directions.size() > 1){
        if(directions.top()){
            current = current->rightChild;
        }
        else{
            current = current->leftChild;
        }
        directions.pop();
    }

    if(directions.top()){
        newNode->parent = current;
        current->rightChild = newNode;
    }
    else {
        newNode->parent = current;
        current->leftChild = newNode;
    }

    this->_heapifyUp(newNode);
};

template <typename T>
T PriorityQueueTree<T>::pop(){
    if(this->_root == nullptr){
        throw std::out_of_range("Queue is empty");
    }
    
    T result = this->_root->val;
    
    if(this->_size == 1){
        delete this->_root;
        this->_root = nullptr;
        this->_size--;
        return result;
    }

    std::stack<bool> directions;
    unsigned int tmp_size = this->_size;
    while(tmp_size > 0){
        directions.push((bool) (tmp_size & 1)); // tmp_size % 2
        tmp_size >>= 1; // tmp_size /= 2
    }
    directions.pop();
    TreeNode<T> * current = this->_root;
    while(directions.size() > 1){
        if(directions.top()){
            current = current->rightChild;
        }
        else{
            current = current->leftChild;
        }
        directions.pop();
    }

    if(directions.top()){
        this->_swap(current->rightChild, this->_root);
        delete current->rightChild;
        current->rightChild = nullptr;
    }
    else {
        this->_swap(current->leftChild, this->_root);
        delete current->leftChild;
        current->leftChild = nullptr;
    }

    this->_size--;
    this->_heapifyDown(this->_root);
    return result;
};

template <typename T>
void PriorityQueueTree<T>::_swap(TreeNode<T> * n1, TreeNode<T> * n2){
    T tmp_val = n1->val;
    int tmp_priority = n1->priority;
    n1->val = n2->val;
    n1->priority = n2->priority;
    n2->val = tmp_val;
    n2->priority = tmp_priority;
};

template <typename T>
void PriorityQueueTree<T>::_heapifyDown(TreeNode<T> * node){
    TreeNode<T> * biggest = node;

    if(node->leftChild != nullptr && biggest->priority < node->leftChild->priority){
        biggest = node->leftChild;
    }

    if(node->rightChild != nullptr && biggest->priority < node->rightChild->priority){
        biggest = node->rightChild;
    }

    if(biggest != node){
        this->_swap(biggest, node);
        this->_heapifyDown(biggest);
    }

};

template <typename T>
void PriorityQueueTree<T>::_heapifyUp(TreeNode<T> * node){
    if(node->parent == nullptr){
        return;
    }

    if(node->priority > node->parent->priority){
        this->_swap(node, node->parent);
        this->_heapifyUp(node->parent);
    }
};

template <typename T>
T PriorityQueueTree<T>::peek() const{
    if(this->_root != nullptr){
        return this->_root->val;
    }
    throw std::out_of_range("Tree is empty");
};



#endif