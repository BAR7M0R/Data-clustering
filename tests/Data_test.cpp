//
// Created by Dell on 10/03/2025.
//
#include "Data.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Data class constructors", "[Data]") {
    SECTION("Default") {
        Data data;
        REQUIRE(data.size() == 0);  // Domyślny konstruktor powinien inicjować pusty wektor
    }

    SECTION("data vector") {
        data_vector range = {{1.0, 2.0}, {3.0, 4.0}};
        Data data(range);
        REQUIRE(data.size() == 2);  // Oczekujemy, że rozmiar wektora wynosi 2
    }
}

TEST_CASE("Data class member functions", "[Data]") {
    data_vector range = {{1.0, 2.0}, {3.0, 4.0}};
    Data data(range);

    SECTION("getX") {
        data_axi x_values = data.getX();
        REQUIRE(x_values.size() == 2);  // Oczekujemy 2 elementy
        REQUIRE(x_values[0] == 1.0);   // Pierwszy punkt x
        REQUIRE(x_values[1] == 3.0);   // Drugi punkt x
    }

    SECTION("getY") {
        data_axi y_values = data.getY();
        REQUIRE(y_values.size() == 2);  // Oczekujemy 2 elementy
        REQUIRE(y_values[0] == 2.0);   // Pierwszy punkt y
        REQUIRE(y_values[1] == 4.0);   // Drugi punkt y
    }

    SECTION("get") {
        data_vector points = data.get();
        REQUIRE(points.size() == 2);   // Oczekujemy 2 punkty
        REQUIRE(points[0].getX() == 1.0);  // Pierwszy punkt X
        REQUIRE(points[0].getY() == 2.0);  // Pierwszy punkt Y
    }

    SECTION("size") {
        REQUIRE(data.size() == 2);  // Rozmiar danych powinien wynosić 2
    }
}

