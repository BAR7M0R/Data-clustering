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

#ifndef DATA_HPP
#define DATA_HPP
#include <vector>
#include <functional>
#include "Point.hpp"

using data_vector = std::vector<Point>;
using data_axi = std::vector<double>;



class Data
{
public:
    Data() = default;
    Data(std::size_t length, Point initValue);
    Data(const Data& d);
    explicit Data(const data_vector& rangeOfData);
    Data(const Data& d, const std::function<Point(const Point&)> &fun);
    [[nodiscard("Data::getX")]] data_axi getX() const;
    [[nodiscard("Data::getY")]] data_axi getY() const;
    [[nodiscard("Data::get")]] data_vector get() const;
    [[nodiscard("Data::getCornerOne")]] Point getCornerOne() const;
    [[nodiscard("Data::getCornerTwo")]] Point getCornerTwo() const;

    Point& operator[](size_t index);
    const Point& operator[](size_t index) const;

    [[nodiscard("Data::getDataCenter")]] Point getDataCenter() const;
    [[nodiscard("Data::size")]] size_t size() const;
    [[nodiscard("Data::empty")]] bool empty() const;
    [[nodiscard("Data::operator==")]] bool operator==(const Data& other) const;
    void print() const;
    [[nodiscard("Data::begin")]] auto begin();
    [[nodiscard("Data::cbegin")]] auto cbegin() const;
    [[nodiscard("Data::end")]] auto end();
    [[nodiscard("Data::cend")]] auto cend() const;
    void push_back(const Point& point);
    void push_back(const Data& data);
    void pop_back();

    ~Data() = default;

private:
    data_vector data_;
};


#endif //DATA_HPP
