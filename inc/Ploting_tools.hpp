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

std::pair<std::uint8_t, std::uint8_t> Sizer(std::pair<std::uint8_t, std::uint8_t> subplotSize, std::size_t plotNumber);

#endif //PLOTING_TOOLS_HPP
