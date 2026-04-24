#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <algorithm> // Do std::is_sorted 
#include "../include/queue/PriorityQueueTree.hpp"

PriorityQueueTree<int> make_test_tree_queue(){
    PriorityQueueTree<int> pq;
    pq.push(12, 9);
    return pq;
}

TEST_CASE("Testy działania kolejki priorytetowej na podstawie drzewa", "[treequeue]"){

    SECTION("Dodawanie elementu o wiekszym priorytecie"){
        int dane = 19;
        int dane_priorytet = 10;
        int oczekiwane = 19;

        PriorityQueueTree<int> pq = make_test_tree_queue();
        pq.push(dane, dane_priorytet);
        int rezultat = pq.peek();
        REQUIRE(rezultat == oczekiwane);
    }

    SECTION("Usuwanie jedynego elementu"){
        int oczekiwane = 12;
        PriorityQueueTree<int> pq = make_test_tree_queue();
        int rezultat = pq.pop();
        REQUIRE(rezultat == oczekiwane);
    }

    SECTION("Zmiana priorytetu na niższy"){
        int dane = 19;
        int dane_priorytet = 10;
        int dane_nowy_priorytet = 2;
        int oczekiwane = 12;

        PriorityQueueTree<int> pq = make_test_tree_queue();
        pq.push(dane, dane_priorytet);
        pq.changePriority(dane, dane_nowy_priorytet);
        int rezultat = pq.peek();
        REQUIRE(rezultat == oczekiwane);
    }

    SECTION("Zmiana priorytetu na wyższy"){
        int dane1 = 19;
        int dane_priorytet1 = 10;
        int dane2 = 33;
        int dane_priorytet2 = 2;
        int dane_nowy_priorytet = 11;
        int oczekiwane = 33;

        PriorityQueueTree<int> pq = make_test_tree_queue();
        pq.push(dane1, dane_priorytet1);
        pq.push(dane2, dane_priorytet2);
        pq.changePriority(dane2, dane_nowy_priorytet);
        int rezultat = pq.peek();
        REQUIRE(rezultat == oczekiwane);
    }

    SECTION("Usuwanie z pustej kolejki (błąd)"){
        PriorityQueueTree<int> pq;
        REQUIRE_THROWS_AS(pq.pop(), std::out_of_range);
    }

    SECTION("Podglądanie z pustej kolejki (błąd)"){
        PriorityQueueTree<int> pq;
        REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
    }

    SECTION("Usuwanie wielu elementów w odpowiedniej kolejności") {
        PriorityQueueTree<int> pq;
        pq.push(10, 1);
        pq.push(20, 5);
        pq.push(30, 3);
        pq.push(40, 10);
        pq.push(50, 0);

        REQUIRE(pq.pop() == 40); // priorytet 10
        REQUIRE(pq.pop() == 20); // priorytet 5
        REQUIRE(pq.pop() == 30); // priorytet 3
        REQUIRE(pq.pop() == 10); // priorytet 1
        REQUIRE(pq.pop() == 50); // priorytet 0
    }

    SECTION("Elementy o takim samym priorytecie") {
        PriorityQueueTree<int> pq;
        pq.push(100, 5);
        pq.push(200, 5);
        pq.push(300, 5);

        int val1 = pq.pop();
        int val2 = pq.pop();
        int val3 = pq.pop();

        REQUIRE((val1 + val2 + val3) == 600); // 100 + 200 + 300
        REQUIRE_THROWS_AS(pq.pop(), std::out_of_range);
    }

    SECTION("Przeplatane operacje push i pop") {
        PriorityQueueTree<int> pq;
        pq.push(100, 10);
        pq.push(200, 5);
        REQUIRE(pq.pop() == 100); // zostało tylko 200 (priorytet 5)
        
        pq.push(300, 20); // wjeżdża z najwyższym priorytetem
        pq.push(400, 2);  // wjeżdża z najniższym
        
        REQUIRE(pq.pop() == 300); 
        REQUIRE(pq.pop() == 200);
        REQUIRE(pq.pop() == 400);
    }

    SECTION("Konstruktor kopiujący (głęboka kopia)") {
        PriorityQueueTree<int> pq1;
        pq1.push(11, 1);
        pq1.push(22, 2);
        pq1.push(33, 3);

        PriorityQueueTree<int> pq2 = pq1; // Tworzymy kopię

        // Zmiana w oryginale nie powinna wpływać na kopię!
        pq1.pop(); 
        pq1.push(99, 99);

        // Sprawdzamy stan niezmienionej kopii (pq2)
        REQUIRE(pq2.pop() == 33);
        REQUIRE(pq2.pop() == 22);
        REQUIRE(pq2.pop() == 11);
        REQUIRE_THROWS_AS(pq2.pop(), std::out_of_range);
    }

    SECTION("Zmiana priorytetu nieistniejącego elementu (zabezpieczenie)") {
        PriorityQueueTree<int> pq = make_test_tree_queue(); // w środku jest (12, 9)
        REQUIRE_THROWS_AS(pq.changePriority(999, 100), std::runtime_error);
    }

    SECTION("Test stresowy (duża ilość danych i sortowanie)") {
        PriorityQueueTree<int> pq;
        
        // Dodajemy 100 elementów
        for(int i = 0; i < 100; i++){
            pq.push(i, i); // Wartość taka sama jak priorytet dla uproszczenia
        }

        // Ściągamy elementy i sprawdzamy czy schodzą idealnie od największego (99 do 0)
        for(int i = 99; i >= 0; i--){
            REQUIRE(pq.pop() == i);
        }
    }

}