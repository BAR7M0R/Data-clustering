//
// Created by Dell on 11/03/2025.
//

#ifndef PLOTING_TOOLS_HPP
#define PLOTING_TOOLS_HPP

#include <cstdint>
#include <string>
#include <utility>

#include "Data.hpp"

void Ploting(const std::vector<Data> &data, const std::string &plotTitle);
void Ploting(const Data& points, const std::vector<std::vector<double>> &weights, const std::vector<Point> &clusterCenters, const std::string &plotTitle);
#endif //PLOTING_TOOLS_HPP
