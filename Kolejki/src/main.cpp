#include "efficency_test/EfficencyTest.hpp"
#include "factory/PriorityQueueTreeFactory.hpp"
#include "factory/PriorityQueueVectorSortedFactory.hpp"
#include <vector>

int main(int argc, char ** argv){
    vector<int> sizes = {20000, 40000, 60000, 80000, 100000, 120000, 140000, 160000, 180000, 200000};
    
    PriorityQueueTreeFactory<int> pqtf;
    EfficencyTest testTree(sizes, &pqtf);
    testTree.test();

    return 0;
}