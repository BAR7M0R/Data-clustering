//
// Created by Dell on 10/03/2025.
//

#include "CrispClustering.hpp"

#include <algorithm>
#include <vector>

using matrixU = std::vector<std::vector<double>>;
using matrixP = std::vector<Point>;
using cluster = std::vector<Point>;

CrispClustering::CrispClustering(const std::vector<Point>& rowData, const size_t& numberOfClusters, const size_t& calculationDepth)
    : Data(rowData)
      , numberOfClusters_(numberOfClusters)
      , calculationDepth_(calculationDepth)
      , previous_(initU())
{
    for (size_t depthIndex(0); depthIndex < calculationDepth_; ++depthIndex)
    {
        next_.resize(size(), std::vector<double>(numberOfClusters_, 0));
        matrixP currentPrototypes = calculatePrototypes(previous_);
        std::vector<double> distances;
        for (size_t pIndex(0); pIndex < size(); ++pIndex)
        {
            for (size_t vIndex(0); vIndex < numberOfClusters_; ++vIndex)
            {
                distances.push_back(currentPrototypes.at(vIndex).distance(get().at(pIndex)));
            }
            const size_t selectedCluster = std::ranges::distance(
                distances.begin(),
                std::ranges::min_element(distances));
            next_.at(pIndex).at(selectedCluster) = 1;
            distances.clear();
        }
        previous_ = next_;
        next_.clear();
    }
    Data rawPoints(get());
    cluster tempCluster;
    for (size_t clusterIndex(0); clusterIndex < numberOfClusters_; ++clusterIndex)
    {
        for (size_t pointIndex(0); pointIndex < size(); ++pointIndex)
        {
            if (previous_.at(pointIndex).at(clusterIndex) == 1)
            {
                tempCluster.push_back(get().at(pointIndex));
            }
        }
        clusters_.emplace_back(tempCluster);
        tempCluster.clear();
    }
}

std::vector<Data> &CrispClustering::getClusters()
{
    return clusters_;
}
matrixU CrispClustering::initU() const
{
    matrixU temp;
    temp.resize(size(), std::vector<double>(numberOfClusters_, 0));

    size_t counter = 0;
    for (auto &row : temp)
    {

        for (size_t j(0); j < numberOfClusters_; ++j)
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
matrixP CrispClustering::calculatePrototypes(const matrixU& currentMatrixU) const
{
    matrixP temp;
    temp.resize(numberOfClusters_, Point(0,0));
    for (size_t i(0); i < temp.size(); ++i)
    {
        Point tempPoint(0,0);
        double tempValue(0);
        for (size_t j(0); j < size(); ++j)
        {
            tempValue += currentMatrixU.at(j).at(i);
            tempPoint += get().at(j)*currentMatrixU.at(j).at(i);
        }
        temp.at(i) = tempPoint / tempValue;
    }
    return temp;
}