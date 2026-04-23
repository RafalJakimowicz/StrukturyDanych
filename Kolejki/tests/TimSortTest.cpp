#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <algorithm> // Do std::is_sorted (opcjonalnie do weryfikacji)
#include "../include/sort/Timsort.hpp"


template <typename T>
void TimSort_sort(std::vector<T>& wektor) {
    TimSort<int> t = TimSort<int>(16);
    t.sort(wektor.begin(), wektor.end());
}

// ---------------------------------------------------------
// TESTY
// ---------------------------------------------------------
TEST_CASE("Testy algorytmu sortowania na liczbach calkowitych", "[sortowanie]") {

    // Catch2 pozwala na proste porównywanie całych wektorów za pomocą ==
    // Jeśli wektory nie są równe, Catch2 ładnie wypisze w konsoli różnice.

    SECTION("Sortowanie standardowego wektora w losowej kolejnosci") {
        std::vector<int> dane = {8, 3, 1, 5, 9, 2, 7, 4, 6};
        std::vector<int> oczekiwane = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Sortowanie pustego wektora nie powoduje bledu (Crash test)") {
        std::vector<int> dane = {};
        std::vector<int> oczekiwane = {};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Sortowanie wektora z jednym elementem") {
        std::vector<int> dane = {42};
        std::vector<int> oczekiwane = {42};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Sortowanie wektora juz posortowanego rosnaco") {
        std::vector<int> dane = {1, 2, 3, 4, 5};
        std::vector<int> oczekiwane = {1, 2, 3, 4, 5};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Sortowanie wektora posortowanego malejaco (Najgorszy przypadek)") {
        std::vector<int> dane = {5, 4, 3, 2, 1};
        std::vector<int> oczekiwane = {1, 2, 3, 4, 5};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Sortowanie wektora z duplikatami") {
        std::vector<int> dane = {4, 1, 3, 4, 1, 4};
        std::vector<int> oczekiwane = {1, 1, 3, 4, 4, 4};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Sortowanie wektora ze wszystkimi elementami takimi samymi") {
        std::vector<int> dane = {7, 7, 7, 7, 7};
        std::vector<int> oczekiwane = {7, 7, 7, 7, 7};
        
        TimSort_sort(dane);
        
        REQUIRE(dane == oczekiwane);
    }

    SECTION("Test przekroczenia progu Insertion Sorta (20 elementow)") {
        std::vector<int> dane = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 
                                10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        TimSort_sort(dane);
        REQUIRE(std::is_sorted(dane.begin(), dane.end()) == true);
    }
    
    // OPCJONALNIE: Test dla bardzo dużej ilości danych
    SECTION("Weryfikacja duzych zbiorow danych (Stress test)") {
        std::vector<int> dane(10000);
        
        // Wypełniamy wektor liczbami od 10000 do 1
        int wartosc = 10000;
        for(auto& element : dane) {
            element = wartosc--;
        }

        TimSort_sort(dane);

        // Zamiast ręcznie tworzyć wektor oczekiwany dla 10000 elementów,
        // używamy funkcji z biblioteki standardowej do weryfikacji.
        REQUIRE(std::is_sorted(dane.begin(), dane.end()) == true);
    }
}