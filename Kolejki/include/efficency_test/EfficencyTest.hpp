#ifndef EFFICENCY_TEST_HPP
#define EFFICENCY_TEST_HPP
#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
#include <iostream>
#include "queue/IQueue.hpp"
#include "factory/IQueueFactory.hpp"

// robimy sekwencujnie w strukturze a wątki dla samych struktur

// kolejnosc testów
// 1 - push
// 2 - pop
// 3 - dostanie rozmiaru
// 4 - peek
// 5 - zmiana priorytetu

// w pliku, nazwa to (testowana struktura).csv
// (numer testu), (ilosc elementów), (śrenia z 100 [ms])
// rozmiary bedą 1k 2k 5k 10k 20k 50k 100k 200k 500k

class EfficencyTest{
    private:
    std::vector<int> _sizes;
    IQueueFactory<int> * _factory;
    std::random_device _rd;
    std::mt19937 _randomGen;
    std::string _filename;
    int _sampleSize;
    double _testPush(int size);
    double _testPop(int size);
    double _testGetSize(int size);
    double _testPeek(int size);
    double _testChangePriority(int size);
    void _runForSize(int size, std::ofstream &file);
    std::unique_ptr<IQueue<int>> _generateQueue(int size);
    public:
    EfficencyTest(std::vector<int> sizes, int sampleSize, IQueueFactory<int> * factory, std::string filename);
    void test();
    ~EfficencyTest();
};

#endif