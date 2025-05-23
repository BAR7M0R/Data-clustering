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
#include "data.hpp"

#include <vector>
#include <algorithm>
#include <iterator>
#include "Point.hpp"

Data::Data(const std::size_t length, const Point initValue)
    : data_(std::vector(length, initValue))
{

}

Data::Data(const Data &d)
: Data(d.get())
{}

Data::Data(const Data& d, const std::function<Point(const Point&)> &fun)
    : Data(d)
{
    std::ranges::for_each(data_, fun);
}

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

data_vector::iterator Data::begin() {
    return data_.begin();
}
data_vector::const_iterator Data::cbegin() const {
    return data_.cbegin();
}
data_vector::iterator Data::end() {
    return data_.end();
}
data_vector::const_iterator Data::cend() const {
    return data_.cend();
}

void Data::push_back(const Point &point) {
    data_.push_back(point);
}

void Data::push_back(const Data &data) {
    data_.reserve(data_.size() + data.size());
    data_.insert(data_.end(), data.cbegin(), data.cend());
}

void Data::pop_back() {
    return data_.pop_back();
}

void Data::reserve(const std::size_t size) {
    data_.reserve(size);
}

Point Data::getCornerOne() const {
    const auto itX = std::ranges::min_element(data_, Point::checkIfFirstXSmaller);
    const auto itY = std::ranges::min_element(data_, Point::checkIfFirstYSmaller);

    if (itX == data_.end() || itY == data_.end()) {
        throw std::runtime_error("lack of Data inside data_");
    }

    double x = itX->getX();
    double y = itY->getY();

    return Point{x, y};
}

Point Data::getCornerTwo() const {
    auto itX = std::ranges::max_element(data_, Point::checkIfFirstXGreater);
    auto itY = std::ranges::max_element(data_, Point::checkIfFirstYGreater);

    if (itX == data_.end() || itY == data_.end()) {
        throw std::runtime_error("lack of Data inside data_");
    }
    return Point{itX->getX(), itY->getY()};
}
Point& Data::operator[](const size_t index){
    return data_[index];
}

const Point& Data::operator[](const size_t index) const {
    return data_[index];
}

x_iterator Data::x_begin() {
    return x_iterator(data_.begin());
}

x_iterator Data::x_end() {
    return x_iterator(data_.end());
}

y_iterator Data::y_begin() {
    return y_iterator(data_.begin());
}

y_iterator Data::y_end() {
    return y_iterator(data_.end());
}
