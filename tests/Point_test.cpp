//
// Created by Dell on 10/03/2025.
//

#include "Point.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Konstrukcja obiektów", "[Point]"){
    SECTION("Konstruktor domyślny") {
        Point p;
        REQUIRE(p.getX() == 0.0);
        REQUIRE(p.getY() == 0.0);
    }

    SECTION("Konstruktor parametryczny") {
        Point p(3.5, -2.5);
        REQUIRE(p.getX() == 3.5);
        REQUIRE(p.getY() == -2.5);
    }

    SECTION("Konstruktor kopiujący") {
        Point p1(1.0, 2.0);
        Point p2(p1);
        REQUIRE(p2.getX() == 1.0);
        REQUIRE(p2.getY() == 2.0);
    }
}

TEST_CASE("Operator przypisania", "[Point]") {
    Point p1(4.0, 5.0);
    Point p2;
    p2 = p1;
    REQUIRE(p2.getX() == 4.0);
    REQUIRE(p2.getY() == 5.0);
}

TEST_CASE("Operator mnożenia przez skalar", "[Point]") {
    Point p(2.0, -3.0);
    Point result = p * 2.0;
    REQUIRE(result.getX() == 4.0);
    REQUIRE(result.getY() == -6.0);
}

TEST_CASE("Operator dodawania", "[Point]") {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    Point result = p1 + p2;
    REQUIRE(result.getX() == 4.0);
    REQUIRE(result.getY() == 6.0);
}

TEST_CASE("Operator dodawania i przypisania", "[Point]") {
    Point p1(2.0, 3.0);
    Point p2(1.0, 1.0);
    p1 += p2;
    REQUIRE(p1.getX() == 3.0);
    REQUIRE(p1.getY() == 4.0);
}

TEST_CASE("Operator odejmowania", "[Point]") {
    Point p1(5.0, 7.0);
    Point p2(2.0, 3.0);
    Point result = p1 - p2;
    REQUIRE(result.getX() == 3.0);
    REQUIRE(result.getY() == 4.0);
}

TEST_CASE("Operator dzielenia przez skalar", "[Point]") {
    Point p(8.0, 6.0);
    Point result = p / 2.0;
    REQUIRE(result.getX() == 4.0);
    REQUIRE(result.getY() == 3.0);
}

TEST_CASE("Obliczanie odległości", "[Point]") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    REQUIRE(p1.distance(p2) == (5.0));
}