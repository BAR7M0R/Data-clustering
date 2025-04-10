/******************************************************************************
 * Copyright 2025, Bartłomiej Głodek
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#ifndef PLOTING_TOOLS_HPP
#define PLOTING_TOOLS_HPP

#include <cstdint>
#include <string>
#include <utility>

#include "Data.hpp"

void Ploting(const std::vector<Data> &data, const std::string &plotTitle);
void Ploting(const Data& points, const std::vector<std::vector<double>> &weights, const std::vector<Point> &clusterCenters, const std::string &plotTitle);
#endif //PLOTING_TOOLS_HPP
