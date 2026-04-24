#ifndef EFFICENCY_TEST_HPP
#define EFFICENCY_TEST_HPP
#include <vector>
#include <fstream>
#include "queue/IQueue.hpp"
#include "factory/IQueueFactory.hpp"
using namespace std;

// robimy sekwencujnie w strukturze a wątki dla samych struktur

// kolejnosc testów
// 1 - push
// 2 - pop
// 3 - dostanie rozmiaru
// 4 - peek
// 5 - zmiana priorytetu

// w pliku, nazwa to (testowana struktura).csv
// (numer testu), (ilosc elementów), (śrenia z 1000)
// rozmiary bedą od 20k do 200k co 20k

class EfficencyTest{
    private:
    vector<int> _sizes;
    IQueueFactory<int> * _factory;
    float _testPush(IQueue<int> &queue);
    float _testPop(IQueue<int> &queue);
    float _testGetSize(IQueue<int> &queue);
    float _testPeek(IQueue<int> &queue);
    float _testChangePriority(IQueue<int> &queue);
    void _runForSize(int size, fstream &file);
    IQueue<int> _generateQueue(int size);
    public:
    EfficencyTest(vector<int> sizes, IQueueFactory<int> * factory);
    void test();
    ~EfficencyTest();
};

#endif