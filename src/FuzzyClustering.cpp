//
// Created by Dell on 10/03/2025.
//

#include "FuzzyClustering.hpp"

#include <cmath>
#include <iostream>

using matrixU = std::vector<std::vector<double>>;
using matrixP = std::vector<Point>;
using cluster = std::vector<Point>;

/*
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
*/

FuzzyClustering::FuzzyClustering(Data rowData, std::size_t clusterNumber, double fuzzyFactor, std::size_t maxIterations,
    double epsilon):clustersNumber_(clusterNumber),
                    fuzzyFactor_(fuzzyFactor),
                    maxIterations_(maxIterations),
                    epsilon_(epsilon),
                    rowData_(std::move(rowData)) {
    if (rowData_.empty() or clustersNumber_ <= 0 or clustersNumber_ > rowData_.size() or fuzzyFactor <= 1.0) {
        throw std::invalid_argument("wrong input");
    }
    initializeMembers();
    auto prev_cost = 0.0;
    for (std::size_t i = 0; i < maxIterations_; i++) {
        updateCenters();
        updateMembers();
        auto cost = computeCost();
        costHistory.push_back(cost);
        if (i > 0u and std::abs(cost - prev_cost) < epsilon)
            break;
        prev_cost = cost;
    }

}

auto FuzzyClustering::get() {
    return std::tie(std::move(rowData_), members_, clustersCenters_, clustersNumber_, costHistory);
}

void FuzzyClustering::initializeMembers() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    members_.resize(clustersNumber_, std::vector<double>(rowData_.size(), 0.0));
    for (std::size_t i = 0u; i < rowData_.size(); i++) {
        double sum = 0.0;
        for (std::size_t j = 0u; j < clustersNumber_; j++) {
            members_[j][i] = dist(gen);
            sum += members_[j][i];
        }
        for (std::size_t j = 0u; j < clustersNumber_; j++) {
            members_[j][i] /= sum;
        }
    }
}

void FuzzyClustering::updateCenters() {
    for (std::size_t i = 0u; i < clustersNumber_; i++) {
        auto temp_view = std::views::iota(0ull, rowData_.size())
                         | std::views::transform([this, i](const size_t j) {
                             return rowData_[j] * std::pow(members_[i][j], fuzzyFactor_);
                         });
        clustersCenters_[i] = std::accumulate(temp_view.begin(), temp_view.end(), Point(0.0, 0.0))
                              / std::accumulate(members_[i].begin(), members_[i].end(), 0.0);
    }
}

void FuzzyClustering::updateMembers() {
    for (int i = 0u; i < clustersNumber_; i++) {
        for (std::size_t j = 0u; j < clustersNumber_; j++) {
            auto temp_view = std::views::iota(0ull, rowData_.size())
                             | std::views::transform([this, i, j](const size_t k) {
                                 return std::pow(rowData_[j].distance(clustersCenters_[i])
                                                 / rowData_[j].distance(clustersCenters_[k]),
                                                 2/(fuzzyFactor_-1));
                             });
            members_[j][i] = 1
                             / std::accumulate(temp_view.begin(), temp_view.end(), 0.0);
        }
    }
}

double FuzzyClustering::computeCost() const {
    double cost = 0.0;
    for (size_t i = 0u; i < rowData_.size(); ++i) {
        for (int j = 0u; j < clustersNumber_; ++j) {
            double dist = rowData_[i].distance(clustersCenters_[j]);
            cost += std::pow(members_[i][j], fuzzyFactor_) * std::pow(dist, 2u);

        }
    }
    return cost;
}
