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
    bool operator==(const Point& p) const;
    [[nodiscard("point::operator+")]] Point operator+(const Point& p) const;
    [[nodiscard("point::operator-")]] Point operator-(const Point& p) const;
    [[nodiscard("point::operator*")]] Point operator*(double mul) const;
    [[nodiscard("point::operator//")]] Point operator/(double dev) const;
    [[nodiscard("point::distance")]] double distance(const Point& second) const;
    [[nodiscard("point::getX")]] double getX() const;
    [[nodiscard("point::getY")]] double getY() const;
    void print() const;
private:
    double x_ = 0.0;
    double y_ = 0.0;
};

#endif //POINT_HPP
