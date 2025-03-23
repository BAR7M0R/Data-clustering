//
// Created by Dell on 10/03/2025.
//

#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:
    Point() = default;
    Point(double x, double y);
    Point& operator+=(const Point& p);
    [[nodiscard("point::operator+")]] Point operator+(const Point& p) const;
    [[nodiscard("point::operator-")]] Point operator-(const Point& p) const;
    [[nodiscard("point::operator*")]] Point operator*(double mul) const;
    [[nodiscard("point::operator//")]] Point operator/(double dev) const;
    [[nodiscard("point::distance")]] double distance(const Point& second) const;
    [[nodiscard("point::getX")]] double getX() const;
    [[nodiscard("point::getY")]] double getY() const;
    void print() const;
private:
    double x_;
    double y_;
};

#endif //POINT_HPP
