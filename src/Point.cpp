//
// Created by Dell on 10/03/2025.
//

#include "Point.hpp"
#include "iostream"
#include <cmath>
#include <random>
Point::Point(const double x, const double y)
    : x_(x)
    , y_(y)
{}

Point::Point(const double xMin, const double xMax, const double yMin, const double yMax) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> xScope(xMin, xMax);
    std::uniform_real_distribution<> yScope(yMin, yMax);
    x_ = xScope(gen);
    y_ = yScope(gen);
}

Point Point::operator*(const double mul) const
{
    return {x_ * mul,y_ * mul};
}
Point& Point::operator+=(const Point& p)
{
    if (this != &p)
    {
        x_ += p.getX();
        y_ += p.getY();
    }
    return *this;
}
bool Point::operator==(const Point &p) const {
    return x_ == p.x_ and y_ == p.y_;
}

Point Point::operator+(const Point& p) const
{
    return {x_ + p.getX(), y_ + p.getY()};
}
Point Point::operator-(const Point& p) const
{
    return {x_ - p.getX(), y_ - p.getY()};
}
Point Point::operator/(const double dev) const
{
    (0 == dev) ? throw std::invalid_argument("0 division") : 0;
    return {x_ / dev, y_ / dev};
}
double Point::distance(const Point& p) const
{
    return sqrt(pow(x_ - p.getX(), 2) + pow(y_ - p.getY(), 2));
}
double Point::getX() const
{
    return x_;
}
double Point::getY() const
{
    return y_;
}

auto Point::get() const -> Point {
    return {x_, y_};
}

bool Point::checkIfFirstXGreater(const Point &first, const Point &second) {
    return first.getX() > second.getX();
}

bool Point::checkIfFirstYGreater(const Point &first, const Point &second) {
    return first.getY() > second.getY();
}

bool Point::checkIfFirstXSmaller(const Point &first, const Point &second) {
    return first.getX() < second.getX();
}

bool Point::checkIfFirstYSmaller(const Point &first, const Point &second) {
    return first.getY() < second.getY();
}

void Point::print() const
{
    std::cout << "x: " << x_ << "y: " << y_ << "\n";
}