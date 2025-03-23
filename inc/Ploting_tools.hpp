//
// Created by Dell on 11/03/2025.
//

#ifndef PLOTING_TOOLS_HPP
#define PLOTING_TOOLS_HPP

#include <compare>

#include "Data.hpp"
#include <utility>

void Ploting(Data first, std::vector<Data> second, const char* plotTitle);

template<typename T1>
std::pair<T1, T1> Sizer(std::pair<T1, T1> subplotSize, const std::size_t plotNumber);
#endif //PLOTING_TOOLS_HPP
