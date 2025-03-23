//
// Created by Dell on 10/03/2025.
//

#ifndef CRISP_CLUSTERING_HPP
#define CRISP_CLUSTERING_HPP

#include "Data.hpp"
#include "Point.hpp"
#include <vector>


class CrispClustering : public Data
{
    using matrixU = std::vector<std::vector<double>>;
    using matrixP = std::vector<Point>;
    using cluster = std::vector<Point>;
public:
    /// <summary>
    /// constructor to calculate crisp clustering it is doing all work for you...
    /// </summary>
    /// <param name="rowData">set of points</param>
    /// <param name="numberOfClusters">number of clusters</param>
    /// <param name="calculationDepth">max number of repetition of grouping</param>
    CrispClustering(const std::vector<Point>& rowData, const size_t& numberOfClusters, const size_t& calculationDepth);
    std::vector<Data> &getClusters();
private:
    [[nodiscard]] matrixU initU() const;
    [[nodiscard]] matrixP calculatePrototypes(const matrixU& currentMatrixU) const;
    const size_t numberOfClusters_;
    const size_t calculationDepth_;
    matrixU previous_;
    matrixU next_;
    std::vector<Data> clusters_;
};

#endif //CRISP_CLUSTERING_HPP
