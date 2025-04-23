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

#include "Data_tools.hpp"
#include <stdexcept>

data_axi DataTools::convertDataXToAxi(const Data &d, const std::function<void(double &)> &operation) {
    auto temp = d.getX();
    std::ranges::for_each(temp, operation);
    return temp;
}

data_axi DataTools::convertDataYToAxi(const Data &d, const std::function<void(double &)> &operation) {
    auto temp = d.getY();
    std::ranges::for_each(temp, operation);
    return temp;
}

data_axi DataTools::convertAxiToAxi(data_axi d, const std::function<void(double &)> &operation) {
    std::ranges::for_each(d, operation);
    return d;
}

data_axi DataTools::calculateError(const data_axi& first, const data_axi& second)
{
    if (first.size() != second.size()) throw std::invalid_argument("DataTools::calculateError -> wrong size");
    data_axi out;
    out.reserve(first.size());
    std::ranges::transform(first
                           , second
                           , std::back_inserter(out)
                           , [](auto a, auto b){return a - b;});
    return out;
}