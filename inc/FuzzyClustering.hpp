//
// Created by Dell on 10/03/2025.
//

#ifndef FUZZYCLUSTERING_HPP
#define FUZZYCLUSTERING_HPP

#include "data.hpp"



class FuzzyClustering : public Data
{
    using matrixU = std::vector<std::vector<double>>;
    using matrixP = std::vector<Point>;
    using cluster = std::vector<Point>;
public:
    FuzzyClustering(const data_vector &rowData, const size_t &numberOfClusters, const double &fuzzyFactor, const size_t &calculationDepth);
    std::vector<Data>& getClusters();

private:
    [[nodiscard]] matrixU initU() const;

    [[nodiscard]] matrixP calculatePrototypes(const matrixU& currentMatrixU) const;

    const size_t numberOfClusters_;
    const size_t calculationDepth_;
    const double fuzzyFactor_;
    matrixU previous_;
    matrixU next_;
    std::vector<Data> clusters_;
};


#endif //FUZZYCLUSTERING_HPP
