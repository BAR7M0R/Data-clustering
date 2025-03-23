//
// Created by Dell on 10/03/2025.
//

#ifndef DATA_HPP
#define DATA_HPP
#include <vector>
#include "Point.hpp"

using data_vector = std::vector<Point>;
using data_axi = std::vector<double>;

class Data
{
public:
    Data::Data() = default;
    explicit Data(const data_vector& rangeOfData);
    [[nodiscard("Data::getX")]] data_axi getX() const;
    [[nodiscard("Data::getY")]] data_axi getY() const;
    [[nodiscard("Data::get")]] data_vector get() const;
    [[nodiscard("Data::size")]] size_t size() const;

private:
    data_vector data_;
};


#endif //DATA_HPP
