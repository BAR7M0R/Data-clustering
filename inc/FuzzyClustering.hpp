//
// Created by Dell on 10/03/2025.
//

#ifndef FUZZYCLUSTERING_HPP
#define FUZZYCLUSTERING_HPP

#include <vector>
#include <cstddef>
#include "data.hpp"

class FuzzyClustering final
{
public:
    FuzzyClustering(const Data &rowData,
        std::size_t clusterNumber,
        double fuzzyFactor = 2.0,
        std::size_t maxIterations = 100u,
        double epsilon = 4);

    std::tuple<Data, std::vector<std::vector<double>>, std::vector<Point>> get();

private:
    void initializeMembers();
    void updateCenters();
    void updateMembers();
    double computeCost() const;

    const std::size_t clustersNumber_;
    const double fuzzyFactor_;
    const std::size_t maxIterations_;
    const double epsilon_;
    const Data rowData_;
    std::vector<Point> clustersCenters_;
    std::vector<std::vector<double>> members_;
    std::vector<double> costHistory;
};


#endif //FUZZYCLUSTERING_HPP
