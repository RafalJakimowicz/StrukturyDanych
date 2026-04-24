#ifndef EFFICENCY_TEST_HPP
#define EFFICENCY_TEST_HPP
#include <vector>
#include <fstream>
#include "../queue/IQueue.hpp"
using namespace std;

// robimy sekwencujnie w strukturze a wątki dla samych struktur

// kolejnosc testów
// 1 - push
// 2 - pop
// 3 - dostanie rozmiaru
// 4 - peek
// 5 - zmiana priorytetu

// w pliku, nazwa to (testowana struktura).csv
// (numer testu), (ilosc elementów), (śrenia z 100)

class EfficencyTest{
    private:
    vector<int> _sizes;
    float _testPush(IQueue<int> queue);
    float _testPop(IQueue<int> queue);
    float _testGetSize(IQueue<int> queue);
    float _testPeek(IQueue<int> queue);
    float _testChangePriority(IQueue<int> queue);
    void _runForSize(int size, fstream * file);
    IQueue<int> _generateQueue(int size);
    public:
    EfficencyTest(vector<int> sizes);
    void test(IQueue<int> queue);
    ~EfficencyTest();
};

#endif