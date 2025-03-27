//
// Created by Dell on 10/03/2025.
//

#include "Point.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cmath>
TEST_CASE("Point class construction", "[Point]"){
    SECTION("default") {
        Point p;
        REQUIRE(p.getX() == 0.0);
        REQUIRE(p.getY() == 0.0);
    }

    SECTION("parametric") {
        Point p(3.5, -2.5);
        REQUIRE(p.getX() == 3.5);
        REQUIRE(p.getY() == -2.5);
    }

    SECTION("copy") {
        Point p1(1.0, 2.0);
        Point p2(p1);
        REQUIRE(p2.getX() == 1.0);
        REQUIRE(p2.getY() == 2.0);
    }
}

TEST_CASE("Point class operators", "[Point]") {
    SECTION("assigment") {
        Point p1(4.0, 5.0);
        Point p2;
        p2 = p1;
        REQUIRE(p2.getX() == 4.0);
        REQUIRE(p2.getY() == 5.0);
    }
    SECTION("Multiplication by scalar") {
        Point p(2.0, -3.0);
        Point result = p * 2.0;
        REQUIRE(result.getX() == 4.0);
        REQUIRE(result.getY() == -6.0);
    }
    SECTION("addiction") {
        Point p1(1.0, 2.0);
        Point p2(3.0, 4.0);
        Point result = p1 + p2;
        REQUIRE(result.getX() == 4.0);
        REQUIRE(result.getY() == 6.0);
    }
    SECTION("subtraction") {
        Point p1(5.0, 7.0);
        Point p2(2.0, 3.0);
        Point result = p1 - p2;
        REQUIRE(result.getX() == 3.0);
        REQUIRE(result.getY() == 4.0);
    }
    SECTION("addition assignment") {
        Point p1(2.0, 3.0);
        Point p2(1.0, 1.0);
        p1 += p2;
        REQUIRE(p1.getX() == 3.0);
        REQUIRE(p1.getY() == 4.0);
    }
    SECTION("division by scalar") {
        struct testDataStruct{
            Point p1;
            double divisor;
            Point result;
        };
        std::vector<testDataStruct> testData{
        {{10.0, 20.0}, 1.0, {10.0, 20.0}},
        {{-10.0, -20.0}, 1.0, {-10.0, -20.0}},
        {{10.0, 20.0}, -1.0, {-10.0, -20.0}},
        {{-10.0, -20.0}, -1.0, {10.0, 20.0}},
        {{10.0, 20.0}, 0.5, {20.0, 40.0}},
        {{10.0, 20.0}, 2.0, {5.0, 10.0}},
        {{-10.0, -20.0}, 2.0, {-5.0, -10.0}},
        {{1000000.0, 2000000.0}, 1000.0, {1000.0, 2000.0}},
        {{1e-6, 2e-6}, 1e-3, {0.001, 0.002}},
        {{-1e6, -2e6}, 1e3, {-1000.0, -2000.0}},
        {{123.456, 789.123}, 3.0, {41.152, 263.041}},
        {{-987.654, -321.987}, 7.0, {-141.093, -45.998}},
        {{5.0, 10.0}, 2.5, {2.0, 4.0}},
        {{-5.0, -10.0}, 2.5, {-2.0, -4.0}},
        {{0.0, 0.0}, 1.0, {0.0, 0.0}},
        {{1.0, 1.0}, 0.1, {10.0, 10.0}},
        {{-1.0, -1.0}, 0.1, {-10.0, -10.0}},
        {{42.0, 84.0}, 6.0, {7.0, 14.0}},
        {{-42.0, -84.0}, 6.0, {-7.0, -14.0}},
        {{99.99, 88.88}, 0.01, {9999.0, 8888.0}},
        };
        for (auto&[p, div, result]: testData) {
            double epsilon = 1e-3;
            Point temp = p / div;
            REQUIRE((std::fabs(temp.getX() - result.getX()) < epsilon) == true);
            REQUIRE((std::fabs(temp.getY() - result.getY()) < epsilon) == true);
        }
    }
}

TEST_CASE("Point class member functions", "[Point]") {
    SECTION("distance function") {
        struct testDataStruct{
            Point p1;
            Point p2;
            double result;
        };
        std::vector<testDataStruct> testData{
        {{0.0, 0.0}, {0.0, 0.0}, 0.0},
        {{1.0, 1.0}, {2.0, 2.0}, std::sqrt(2.0)},
        {{-1.0, -1.0}, {1.0, 1.0}, std::sqrt(8.0)},
        {{3.0, 4.0}, {0.0, 0.0}, 5.0},
        {{-3.0, -4.0}, {0.0, 0.0}, 5.0},
        {{5.0, 5.0}, {10.0, 10.0}, std::sqrt(50.0)},
        {{2.5, 2.5}, {5.0, 5.0}, std::sqrt(12.5)},
        {{-2.5, -2.5}, {5.0, 5.0}, std::sqrt(112.5)},
        {{100.0, 200.0}, {300.0, 400.0}, std::sqrt(80000.0)},
        {{-100.0, -200.0}, {300.0, 400.0}, std::sqrt(520000.0)},
        {{6.0, 8.0}, {0.0, 0.0}, 10.0},
        {{7.0, 24.0}, {0.0, 0.0}, 25.0},
        {{1.5, 1.5}, {3.0, 3.0}, std::sqrt(4.5)},
        {{-1.5, -1.5}, {3.0, 3.0}, std::sqrt(40.5)},
        {{9.0, 12.0}, {0.0, 0.0}, 15.0},
        {{15.0, 20.0}, {0.0, 0.0}, 25.0},
        {{-10.0, -10.0}, {10.0, 10.0}, std::sqrt(800.0)},
        {{-20.0, -30.0}, {40.0, 50.0}, std::sqrt(10000.0)},
        {{50.0, 60.0}, {0.0, 0.0}, std::sqrt(6100.0)},
        {{-50.0, -60.0}, {50.0, 60.0}, std::sqrt(24400.0)}
        };
        for (auto&[p1, p2, result]: testData) {
            double epsilon = 1e-3;
            CAPTURE(p1.getX(), p1.getY(), p2.getX(), p2.getY(), result);
            REQUIRE((std::fabs(p1.distance(p2) - result) < epsilon) == true);
        }
    }
}