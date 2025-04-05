//
// Created by Dell on 10/03/2025.
//

#include "FuzzyClustering.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <ranges>
#include <tuple>

using matrixU = std::vector<std::vector<double>>;
using matrixP = std::vector<Point>;
using cluster = std::vector<Point>;

FuzzyClustering::FuzzyClustering(const Data &rowData, std::size_t clusterNumber, double fuzzyFactor, std::size_t maxIterations,
    double epsilon):clustersNumber_(clusterNumber),
                    fuzzyFactor_(fuzzyFactor),
                    maxIterations_(maxIterations),
                    epsilon_(epsilon),
                    rowData_(rowData) {
    if (rowData_.empty() or clustersNumber_ <= 0 or clustersNumber_ > rowData_.size() or fuzzyFactor <= 1.0) {
        throw std::invalid_argument("wrong input");
    }
    clustersCenters_ = std::vector<Point>(clustersNumber_);
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

std::tuple<Data, std::vector<std::vector<double>>, std::vector<Point>> FuzzyClustering::get() {
    return std::make_tuple(rowData_, members_, clustersCenters_);
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
        auto numeratorPreTransform  = std::views::iota(0ull, rowData_.size())
                         | std::views::transform([this, i](const size_t j) {
                                return rowData_[j] * std::pow(members_[i][j], fuzzyFactor_);
        });
        auto denominatorPreTransform = std::views::iota(0ull, rowData_.size())
        | std::views::transform([this, i](const size_t j) {return pow(members_[i][j], fuzzyFactor_); });
        const Point numerator  = std::accumulate(numeratorPreTransform .begin(), numeratorPreTransform .end(), Point{0.0,0.0}, [](const Point &p, const Point &q) {return p+q;});
        const double denominator = std::accumulate(denominatorPreTransform.begin(), denominatorPreTransform.end(), 0.0);
        clustersCenters_[i] = numerator / denominator;
    }
}

void FuzzyClustering::updateMembers() {
    for (std::size_t i = 0ull; i < clustersNumber_; i++) {
        for (std::size_t j = 0ull; j < rowData_.size(); j++) {
            auto temp_view = std::views::iota(0ull, clustersNumber_)
                             | std::views::transform([this, i, j](const size_t k) {
                                 return std::pow(rowData_[j].distance(clustersCenters_[i])
                                               / rowData_[j].distance(clustersCenters_[k])
                                               , 2/(fuzzyFactor_-1));
                             });

            members_[i][j] = 1.0 / std::accumulate(temp_view.begin(), temp_view.end(), 0.0);
        }
    }
}

double FuzzyClustering::computeCost() const {
    double cost = 0.0;
    for (size_t i = 0u; i < rowData_.size(); ++i) {
        for (int j = 0u; j < clustersNumber_; ++j) {
            const double dist = rowData_[i].distance(clustersCenters_[j]);
            cost += std::pow(members_[j][i], fuzzyFactor_) * std::pow(dist, 2.0);

        }
    }
    return cost;
}
