//
// Created by Dell on 10/03/2025.
//

#include "Point.hpp"
#include "iostream"
#include <cmath>
Point::Point(const double x, const double y)
    : x_(x)
    , y_(y)
{}
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
void Point::print() const
{
    std::cout << "x: " << x_ << "y: " << y_ << "\n";
}
