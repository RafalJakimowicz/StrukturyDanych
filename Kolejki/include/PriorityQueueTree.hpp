#ifndef PRIORITY_QUEUE_TREE_HPP
#define PRIORITY_QUEUE_TREE_HPP
#include "Queue.hpp"

template <typename T>
struct TreeNode{
    TreeNode * leftChild;
    TreeNode * rightChild;
    T val;
    unsigned long priority;
};

template <typename T>
class PriorityQueueTree:Queue<T>{

    
};

#endif