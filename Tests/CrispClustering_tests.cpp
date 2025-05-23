//
// Created by Dell on 10/03/2025.
//
#include "CrispClustering.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("CrispClustering full algorithm", "[CrispClustering]") {
    const std::vector<Point> points = {Point(0,0), Point(0,1), Point(1,0), Point(1,1),
                                 Point(10,10), Point(10,11), Point(11,10), Point(11,11)};
    constexpr size_t numberOfClusters = 2;
    constexpr size_t calculationDepth = 10;
    CrispClustering clustering(points,numberOfClusters,calculationDepth);

    const std::vector<Data> clusters = clustering.getClusters();
    REQUIRE(clusters.size() == 2);

    const Data cluster0 = clusters[0];
    const Data cluster1 = clusters[1];


    const Data expected_cluster0({Point(0,0), Point(0,1), Point(1,0), Point(1,1)});
    const Data expected_cluster1({Point(10,10), Point(10,11), Point(11,10), Point(11,11)});
    auto result = (cluster0 == expected_cluster0 and cluster1 == expected_cluster1);
    REQUIRE(result);


}