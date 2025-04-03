//
// Created by Dell on 10/03/2025.
//

#include "data.hpp"

#include <vector>
#include <algorithm>
#include <ranges>
#include "Point.hpp"
#include <iostream>
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
    return data_.size();
}

bool Data::empty() const {
    return data_.empty();
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

void Data::print() const {
    for (auto p: data_) {
        p.print();
    }
}

Point Data::getCornerOne() const {
    const auto itX = std::ranges::min_element(data_, Point::checkIfFirstXSmaller);
    const auto itY = std::ranges::min_element(data_, Point::checkIfFirstYSmaller);

    if (itX == data_.end() || itY == data_.end()) {
        throw std::runtime_error("lack of data inside data_");
    }

    double x = itX->getX();
    double y = itY->getY();

    return Point{x, y};
}

Point Data::getCornerTwo() const {
    auto itX = std::ranges::max_element(data_, Point::checkIfFirstXGreater);
    auto itY = std::ranges::max_element(data_, Point::checkIfFirstYGreater);

    if (itX == data_.end() || itY == data_.end()) {
        throw std::runtime_error("lack of data inside data_");
    }

    double x = itX->getX();
    double y = itY->getY();

    return Point{x, y};
}
Point Data::operator[](const size_t index) const {
    return data_[index];
}