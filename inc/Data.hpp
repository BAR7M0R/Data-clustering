//
// Created by Dell on 10/03/2025.
//

#ifndef DATA_HPP
#define DATA_HPP
#include <vector>
#include <ostream>
#include "Point.hpp"
using data_vector = std::vector<Point>;
using data_axi = std::vector<double>;



class Data
{
public:
    Data() = default;
    Data(std::size_t length, Point initValue);
    explicit Data(const data_vector& rangeOfData);
    [[nodiscard("Data::getX")]] data_axi getX() const;
    [[nodiscard("Data::getY")]] data_axi getY() const;
    [[nodiscard("Data::get")]] data_vector get() const;
    [[nodiscard("Data::getCornerOne")]] Point getCornerOne() const;
    [[nodiscard("Data::getCornerTwo")]] Point getCornerTwo() const;

    Point& operator[](size_t index);
    const Point& operator[](size_t index) const;

    [[nodiscard("Data::getDataCenter")]] Point getDataCenter() const;
    [[nodiscard("Data::size")]] size_t size() const;
    bool empty() const;
    bool operator==(const Data &other) const;
    void print() const;

    void push_back(const Point &point);
    void pop_back();


private:
    data_vector data_;
};



#endif //DATA_HPP
