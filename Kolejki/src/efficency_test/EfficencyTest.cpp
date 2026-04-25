#include "efficency_test/EfficencyTest.hpp"
using namespace std;

EfficencyTest::EfficencyTest(vector<int> sizes, IQueueFactory<int> * factory) : _randomGen(_rd()) {
    this->_sizes = sizes;
    this->_factory = factory;
};

unique_ptr<IQueue<int>> EfficencyTest::_generateQueue(int size){
    auto queue = this->_factory->create();
    for(int i = 0; i < size; i++){
        queue->push(_randomGen(), _randomGen() % 100000);
    }
    return queue;
}

