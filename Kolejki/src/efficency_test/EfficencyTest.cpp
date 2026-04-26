#include "efficency_test/EfficencyTest.hpp"
using namespace std;

EfficencyTest::EfficencyTest(vector<int> sizes, int sampleSize,  IQueueFactory<int> * factory, string filename) : _randomGen(_rd()) {
    this->_sizes = sizes;
    this->_factory = factory;
    this->_sampleSize = sampleSize;
    this->_filename = filename;
};

unique_ptr<IQueue<int>> EfficencyTest::_generateQueue(int size){
    auto queue = this->_factory->create();
    for(int i = 0; i < size; i++){
        queue->push(_randomGen(), _randomGen() % 100000);
    }
    return queue;
}

double EfficencyTest::_testPush(int size){
    double totalRuntime = 0.00;
    int itemVal = this->_randomGen();
    unsigned int itemPriority = this->_randomGen() % 2000000;
    for(int i = 0; i < this->_sampleSize; i++){
        auto queue = this->_generateQueue(size);
        
        auto start = chrono::high_resolution_clock::now();
        queue->push(itemVal, itemPriority);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> delta = stop - start;
        totalRuntime += delta.count();
    }

    return totalRuntime / this->_sampleSize;
}

double EfficencyTest::_testPop(int size){
    double totalRuntime = 0.00;
    for(int i = 0; i < this->_sampleSize; i++){
        auto queue = this->_generateQueue(size);
        
        auto start = chrono::high_resolution_clock::now();
        queue->pop();
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> delta = stop - start;
        totalRuntime += delta.count();
    }

    return totalRuntime / this->_sampleSize;
}

double EfficencyTest::_testGetSize(int size){
    double totalRuntime = 0.00;
    for(int i = 0; i < this->_sampleSize; i++){
        auto queue = this->_generateQueue(size);
        
        auto start = chrono::high_resolution_clock::now();
        queue->size();
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> delta = stop - start;
        totalRuntime += delta.count();
    }

    return totalRuntime / this->_sampleSize;
}

double EfficencyTest::_testPeek(int size){
    double totalRuntime = 0.00;
    for(int i = 0; i < this->_sampleSize; i++){
        auto queue = this->_generateQueue(size);
        
        auto start = chrono::high_resolution_clock::now();
        queue->peek();
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> delta = stop - start;
        totalRuntime += delta.count();
    }

    return totalRuntime / this->_sampleSize;
}

double EfficencyTest::_testChangePriority(int size){
    double totalRuntime = 0.00;
    unsigned int itemPriority = this->_randomGen() % 2000000;
    for(int i = 0; i < this->_sampleSize; i++){
        auto queue = this->_generateQueue(size);
        int val = queue->peek();
        
        auto start = chrono::high_resolution_clock::now();
        queue->changePriority(val, itemPriority);
        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> delta = stop - start;
        totalRuntime += delta.count();
    }

    return totalRuntime / this->_sampleSize;
}

void EfficencyTest::_runForSize(int size, ofstream &file){
    if(file.is_open()){
        double pushResult = this->_testPush(size);
        double popResult = this->_testPop(size);
        double sizeResult = this->_testGetSize(size);
        double peekResult = this->_testPeek(size);
        double changeResult = this->_testChangePriority(size);

        file << fixed << setprecision(8);
        file << "1," << size << "," << pushResult << endl;
        file << "2," << size << "," << popResult << endl;
        file << "3," << size << "," << sizeResult << endl;
        file << "4," << size << "," << peekResult << endl;
        file << "5," << size << "," << changeResult << endl;
        file.flush();
    } else {
        cerr << "Output file is closed!!" << endl;
    }
}

void EfficencyTest::test(){
    ofstream outFile(this->_filename, ios::app);
    outFile << "Test type, element count, mean time [ms]" << endl;
    outFile.flush();

    if(!outFile.is_open()){
        cout << "File could not open..." << endl;
        return;
    }

    for(int size: this->_sizes){
        cout << "Running tests for: " << this->_filename << " on size: " << size << endl;
        this->_runForSize(size, outFile);
    }

    outFile.close();
    cout << "All completed!!" << endl;
}

EfficencyTest::~EfficencyTest(){
    return;
}