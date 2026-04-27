#include "efficency_test/EfficencyTest.hpp"
#include "factory/PriorityQueueTreeFactory.hpp"
#include "factory/PriorityQueueVectorSortedFactory.hpp"
#include <vector>
#include <thread>
#include "factory/IQueueFactory.hpp"

int main(int argc, char ** argv){
    std::vector<int> sizes = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    
    PriorityQueueTreeFactory<int> pqtf;
    PriorityQueueVectorSortedFactory<int> pqvsf;

    EfficencyTest testTree(sizes, 100, &pqtf, "tree.csv");
    EfficencyTest testVector(sizes, 100, &pqvsf, "vector.csv");

    std::thread treeThread(&EfficencyTest::test, &testTree);
    std::thread vectorThread(&EfficencyTest::test, &testVector);

    if(treeThread.joinable()){
        treeThread.join();
    }

    if(vectorThread.joinable()){
        vectorThread.join();
    }

    return 0;
}