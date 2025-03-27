//
// Created by Dell on 11/03/2025.
//

#ifndef PLOTING_TOOLS_HPP
#define PLOTING_TOOLS_HPP

#include <compare>
#include <cstdint>

#include "Data.hpp"
#include <utility>

void Ploting(Data first, std::vector<Data> second, const char* plotTitle);

std::pair<std::uint8_t, std::uint8_t> Sizer(std::pair<std::uint8_t, std::uint8_t> subplotSize, std::size_t plotNumber);

#endif //PLOTING_TOOLS_HPP
