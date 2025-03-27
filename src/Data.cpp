//
// Created by Dell on 10/03/2025.
//

#include "data.hpp"

#include <vector>
#include <algorithm>
#include <ranges>
#include "Point.hpp"

Data::Data(const std::vector<Point>& rangeOfData)
: data_(rangeOfData)
{}

std::vector<double> Data::getX() const
{
    std::vector<double> X;
    std::ranges::transform(data_, std::back_inserter(X), [](const Point& data) { return data.getX(); });
    return X;
}
std::vector<double> Data::getY() const
{
    std::vector<double> Y;
    std::ranges::transform(data_, std::back_inserter(Y), [](const Point& data) { return data.getY(); });
    return Y;
}
std::vector<Point> Data::get() const
{
    return data_;
}
size_t Data::size() const
{
    return(data_.size());
}
bool Data::operator==(const Data& other) const {
    if (other.size() != size()) {
        throw std::runtime_error("Data::operator==: Size mismatch");
    }
    bool result = true;
    for (size_t i = 0; i < size(); ++i) {
        result = data_[i] == other.get()[i];
        if (!result) break;
    }
    return result;
}
