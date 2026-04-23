#ifndef PRIORITY_QUEUE_TREE_HPP
#define PRIORITY_QUEUE_TREE_HPP
#include "IQueue.hpp"

template <typename T>
struct TreeNode{
    TreeNode * leftChild;
    TreeNode * rightChild;
    T val;
    unsigned int priority;
};

template <typename T>
class PriorityQueueTree:IQueue<T>{
    private:
    void _insertInPlace(TreeNode * node);
    void _swap(TreeNode * n1, TreeNode* n2);
    TreeNode * _root;
    public:
    PriorityQueueTree(){
        this->_size=0;
    }
    void push(T &item, unsigned long priority) override;
    T& peek() override;
    T& pop() override;
};



#endif