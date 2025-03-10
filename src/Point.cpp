//
// Created by Dell on 10/03/2025.
//

#include "Point.hpp"
#include "iostream"
#include <cmath>

Point::Point()
    : x_(0)
    , y_(0)
{}
Point::Point(const double &x, const double &y)
    : x_(x)
    , y_(y)
{}
Point& Point::operator=(const Point &p) {
    if (this != &p) {
        x_ = p.x_;
        y_ = p.y_;
    }
    return *this;
}
Point Point::operator*(const double &mul)
{
    x_ *= mul;
    y_ *= mul;
    return *this;
}
Point& Point::operator+=(const Point& p)
{
    if (this != &p)
    {
        x_ += p.x_;
        y_ += p.y_;
    }
    return *this;
}
Point Point::operator+(const Point& p)
{
    if (this != &p)
    {
        Point temp(*this);
        temp.x_ += p.x_;
        temp.y_ += p.y_;
    }
    return *this;
}
Point& Point::operator-(const Point& p)
{
    if (this != &p) {
        x_ -= p.x_;
        y_ -= p.y_;
    }
    return *this;
}
Point& Point::operator/(const double& dev)
{
    if (dev == 0)
    {
        throw std::invalid_argument("0 division");
    }
    x_ /= dev;
    y_ /= dev;
    return *this;
}
double Point::distance(const Point& second) const
{
    return sqrt(pow(x_ - second.x_, 2) + pow(y_ - second.y_, 2));
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
