#include "efficency_test/EfficencyTest.hpp"
#include "factory/PriorityQueueTreeFactory.hpp"
#include "factory/PriorityQueueVectorSortedFactory.hpp"
#include <vector>

int main(int argc, char ** argv){
    std::vector<int> sizes = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    
    PriorityQueueTreeFactory<int> pqtf;
    EfficencyTest testTree(sizes, 100, &pqtf, "tree.csv");
    testTree.test();

    return 0;
}