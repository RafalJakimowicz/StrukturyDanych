#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>
#include <execution>
#include <vector>
#include <string>
#include <sstream>
#include <future>
#include "DoublyLinkedList.hpp"
#include "DynamicTable.hpp"

DoublyLinkedList<uint32_t> createList(unsigned long lenght);
DynamicTable<uint32_t> createTable(unsigned long lenght);
void testLinkedList(uint32_t len, std::string directory);
void testDynamicTable(uint32_t len, std::string directory);

int main(int argc, char** argv){
    std::vector<uint32_t> lenghts {10000, 20000, 30000, 40000, 50000};
    std::string dir = "wyniki";
    if(std::filesystem::create_directories(dir)){
        std::cout << "Utworzono folder dla wyników" << std::endl;
    }
    else{
        std::cout << "Wystapil problem albo folder istnieje" << std::endl;
    }

    // 1. Zlecamy pierwszą zrównolegloną pętlę do pracy w tle
    auto taskList = std::async(std::launch::async, [&]() {
        std::for_each(std::execution::par, lenghts.begin(), lenghts.end(), [&](uint32_t n) {
            testLinkedList(n, dir);
        });
    });

    // 2. Zlecamy drugą zrównolegloną pętlę do pracy w tle
    auto taskTable = std::async(std::launch::async, [&]() {
        std::for_each(std::execution::par, lenghts.begin(), lenghts.end(), [&](uint32_t n) {
            testDynamicTable(n, dir);
        });
    });

    // 3. Główny wątek czeka, aż obie zrównoleglone pętle zakończą pracę
    taskList.wait();
    taskTable.wait();

    std::cout << "Ukonczono" << std::endl;

    return 0;
}

DoublyLinkedList<uint32_t> createList(unsigned long lenght){
    std::random_device rd;
    std::mt19937 gen(rd());
    DoublyLinkedList<uint32_t> list = DoublyLinkedList<uint32_t>();
    for(unsigned long i = 0; i < lenght; i++){
        list.append(gen());
    }
    return list;
}

DynamicTable<uint32_t> createTable(unsigned long lenght){
    std::random_device rd;
    std::mt19937 gen(rd());
    DynamicTable<uint32_t> table = DynamicTable<uint32_t>(lenght);
    for(unsigned long i = 0; i < lenght; i++){
        table.append(gen());
    }
    return table;
}

void testDynamicTable(uint32_t len, std::string directory){
    // dla losowego indeksu
    std::random_device rd;
    std::mt19937 gen(rd());

    //przyszykowanie pliku
    std::stringstream sstream;
    sstream << directory << '/' << len << "_tablica.csv";
    std::string filename = sstream.str();
    std::ofstream resultFile(filename, std::ios::app);

    //glowna petla
    for(int i = 0; i < 50; i++){
        DynamicTable<uint32_t> table = createTable(len);

        //test 0
        auto start = std::chrono::high_resolution_clock::now();
        table.insert(32, 0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> delta = end - start;
        resultFile << "0," << delta.count() << std::endl;

        //test 1
        start = std::chrono::high_resolution_clock::now();
        table.insert(32, table.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "1," << delta.count() << std::endl;

        //test 2
        start = std::chrono::high_resolution_clock::now();
        //wybiera indeks od 100 do len - 100
        table.insert(32, (gen() % (len - 200)) + 100);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "2," << delta.count() << std::endl;

        //test 3
        start = std::chrono::high_resolution_clock::now();
        table.remove(0);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "3," << delta.count() << std::endl;

        //test 4
        start = std::chrono::high_resolution_clock::now();
        table.remove(table.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "4," << delta.count() << std::endl;

        //test 5
        start = std::chrono::high_resolution_clock::now();
        //wybiera indeks od 100 do len - 100
        table.remove((gen() % (len - 200)) + 100);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "5," << delta.count() << std::endl;


        //test 6
        start = std::chrono::high_resolution_clock::now();
        table.find(32);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "6," << delta.count() << std::endl;

        resultFile.flush();
    }
}

void testLinkedList(uint32_t len, std::string directory){
    // dla losowego indeksu
    std::random_device rd;
    std::mt19937 gen(rd());

    //przyszykowanie pliku
    std::stringstream sstream;
    sstream << directory << '/' << len << "_lista.csv";
    std::string filename = sstream.str();
    std::ofstream resultFile(filename, std::ios::app);

    //glowna petla
    for(int i = 0; i < 50; i++){
        DoublyLinkedList<uint32_t> list = createList(len);

        //test 0
        auto start = std::chrono::high_resolution_clock::now();
        list.insert(32, 0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> delta = end - start;
        resultFile << "0," << delta.count() << std::endl;

        //test 1
        start = std::chrono::high_resolution_clock::now();
        list.insert(32, list.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "1," << delta.count() << std::endl;

        //test 2
        start = std::chrono::high_resolution_clock::now();
        //wybiera indeks od 100 do len - 100
        list.insert(32, (gen() % (len - 200)) + 100);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "2," << delta.count() << std::endl;

        //test 3
        start = std::chrono::high_resolution_clock::now();
        list.remove(0);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "3," << delta.count() << std::endl;

        //test 4
        start = std::chrono::high_resolution_clock::now();
        list.remove(list.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "4," << delta.count() << std::endl;

        //test 5
        start = std::chrono::high_resolution_clock::now();
        //wybiera indeks od 100 do len - 100
        list.remove((gen() % (len - 200)) + 100);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "5," << delta.count() << std::endl;


        //test 6
        start = std::chrono::high_resolution_clock::now();
        list.find(32);
        end = std::chrono::high_resolution_clock::now();
        delta = end - start;
        resultFile << "6," << delta.count() << std::endl;

        resultFile.flush();
    }
}

// 5 rozmiarow co 10k od 10k do 50k; 50 prob dla kazdego testu (7 testow). wychodzi 1750 prob dla kazdej struktury
// na pojedynczej liscie bedzie zrobiony kazdy test jeden po drugim zeby oszczedzic generacje struktur
// kazdy test dla rozmiaru odpalic trzeba w innym watku. i kazdy kazda struktura ma swoje watki czyli 10 watkow.
// indexy: dodawanie pocztaek (0), dodawanie na koniec (1), dodawanie na losowy indeks (2)
// indexy: usuwanie poczatek (3), usuwanie z konca (4), usuwanie z losowego indeksu (5)
// indexy: wyszukiwanie indeksu danego elementu (6)
// format w pliku (csv): {index testu},{czas (ns)} 
// nazwa pliku csv to {n elementow}_{lista / tablica}.csv
// w folderze wyniki
// co daje format np. ./wyniki/10000_lista.csv