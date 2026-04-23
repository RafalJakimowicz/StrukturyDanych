#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <algorithm> // Do std::is_sorted 
#include "../include/PriorityQueueVectorSorted.hpp"
#include "../include/IQueue.hpp"

PriorityQueueVectorSorted<int> make_queue(){
    PriorityQueueVectorSorted<int> pq;
    pq.push(12, 9);
    return pq;
}

TEST_CASE("Testy działania kolejki priorytetowej na podstawie posortowanego vectora", "[vectorqueue]"){

    SECTION("Dodawanie elementu o wiekszym priorytecie"){
        int dane = 19;
        int dane_priorytet = 10;
        int oczekiwane = 19;

        PriorityQueueVectorSorted<int> pq = make_queue();
        pq.push(dane, dane_priorytet);
        int rezultat = pq.peek();
        REQUIRE(rezultat == oczekiwane);
    }

}