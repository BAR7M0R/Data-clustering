//
// Created by Dell on 10/03/2025.
//

#include "FuzzyClustering.hpp"

#include <cmath>
#include <iostream>

using matrixU = std::vector<std::vector<double>>;
using matrixP = std::vector<Point>;
using cluster = std::vector<Point>;

FuzzyClustering::FuzzyClustering(const std::vector<Point> &rowData, const size_t &numberOfClusters, const double &fuzzyFactor, const size_t &calculationDepth)
    : Data(rowData)
    , numberOfClusters_(numberOfClusters)
    , calculationDepth_(calculationDepth)
    , fuzzyFactor_(fuzzyFactor)
    , previous_(initU())
{
    for (size_t depthIndex(0); depthIndex < calculationDepth_; ++depthIndex)
    {
        next_.resize(size(), std::vector<double>(numberOfClusters_, 0));
        matrixP currentPrototypes = calculatePrototypes(previous_);
        std::vector<double> distances;
        for (size_t pointIndex(0); pointIndex < size(); ++pointIndex)
        {

            for (size_t assignedClusterIndex(0); assignedClusterIndex < numberOfClusters_; ++assignedClusterIndex)
            {
                double assignedClusterDistance = get().at(pointIndex).distance(currentPrototypes.at(assignedClusterIndex));
                assignedClusterDistance = pow(assignedClusterDistance, (-2.) / (fuzzyFactor_ - 1));
                double totalDistances = 0;
                for (size_t clusterIndex(0); clusterIndex < numberOfClusters_; ++clusterIndex)
                {
                    double tempDistance = get().at(pointIndex).distance(currentPrototypes.at(clusterIndex));
                    tempDistance = pow(tempDistance, (-2.) / (fuzzyFactor_ - 1));
                    totalDistances += tempDistance;
                }
                next_.at(pointIndex).at(assignedClusterIndex) = assignedClusterDistance / totalDistances;
            }

        }
        previous_ = next_;
        next_.clear();
        for (const auto& i : previous_)
        {
            for (auto j : i)
                std::cout << j << " ";
            std::cout << std::endl;
        }

    }
    Data rawPoints(get());
    cluster tempCluster;
    for (size_t clusterIndex(0); clusterIndex < numberOfClusters_; ++clusterIndex)
    {
        for (size_t pointIndex(0); pointIndex < size(); ++pointIndex)
        {
            if (previous_.at(pointIndex).at(clusterIndex) >= .5)
            {
                tempCluster.push_back(get().at(pointIndex));
            }
        }
        clusters_.emplace_back(tempCluster);
        tempCluster.clear();
    }
}
std::vector<Data>& FuzzyClustering::getClusters()
{
    return clusters_;
}

matrixU FuzzyClustering::initU() const
{
    matrixU temp;
    temp.resize(size(), std::vector<double>(numberOfClusters_, 0));

    size_t counter = 0;
    for (auto& row : temp)
    {

        for (size_t j = 0; j < numberOfClusters_; ++j)
        {
            if (j == counter)
            {
                row.at(j) = 1;
            }
        }
        ++counter;
        if (counter >= numberOfClusters_)
        {
            counter = 0;

        }
    }
    return temp;
}
matrixP FuzzyClustering::calculatePrototypes(const matrixU& currentMatrixU) const
{
    matrixP temp;
    temp.resize(numberOfClusters_, Point(0, 0));
    for (size_t i(0); i < temp.size(); ++i)
    {
        Point tempPoint(0, 0);
        double tempValue(0);
        for (size_t j(0); j < size(); ++j)
        {
            tempValue += currentMatrixU.at(j).at(i);
            tempPoint += get().at(j) * currentMatrixU.at(j).at(i);
        }
        temp.at(i) = tempPoint / tempValue;
    }
    return temp;
}

