//
// Created by Dell on 10/03/2025.
//

#include <FuzzyClustering.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("FuzzyClustering full algorithm", "[FuzzyClustering]") {
    const Data testPoints({
        Point(0., 0.), Point(0., 1.), Point(1., 0.), Point(1., 1.),
        Point(10., 10.), Point(10., 11.), Point(11., 10.), Point(11., 11.)
    });
    const std::vector<std::vector<bool>> possibleOutput1 = {
        {true, true, true, true, false, false, false, false},
        {false, false, false, false, true, true, true, true}
    };
    const std::vector<std::vector<bool>> possibleOutput2 = {
        {false, false, false, false, true, true, true, true},
        {true, true, true, true, false, false, false, false}
    };
    std::vector<bool> expected2 = {false, false, true, true};

    constexpr size_t numberOfClusters = 2;
    constexpr size_t calculationDepth = 100;
    constexpr double epsilon = 2;
    FuzzyClustering clustering(testPoints, numberOfClusters, epsilon, calculationDepth);
    auto [points, membershipment, centroids] = clustering.get();
    REQUIRE(centroids.size() == numberOfClusters);
    REQUIRE(membershipment.size() == numberOfClusters);
    REQUIRE(membershipment[0].size() == testPoints.size());
    REQUIRE(points.size() == testPoints.size());
    std::vector classifycatedMembers(
        possibleOutput1.size(), std::vector(possibleOutput1[0].size(), false));
    for (size_t cluster = 0ull; cluster < numberOfClusters; ++cluster) {
        for (size_t member = 0ull; member < membershipment[cluster].size(); ++member) {
            classifycatedMembers[cluster][member] = membershipment[cluster][member] > 0.5;
        }
    }
    for (size_t cluster = 0ull; cluster < numberOfClusters; ++cluster) {
        for (size_t member = 0ull; member < membershipment[cluster].size(); ++member) {
            bool case1 = classifycatedMembers[cluster][member] == possibleOutput1[cluster][member];
            bool case2 = classifycatedMembers[cluster][member] == possibleOutput2[cluster][member];
            REQUIRE((case1 || case2));
        }
    }
}




