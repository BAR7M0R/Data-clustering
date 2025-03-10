//
// Created by Dell on 10/03/2025.
//

#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:
    Point();
    Point(const double &x, const double &y);
    Point(const Point &p) = default;
    Point& operator=(const Point &p);
    Point operator*(const double &mul);
    Point& operator+=(const Point& p);
    Point operator+(const Point& p);
    Point& operator-(const Point& p);
    Point& operator/(const double& dev);
    [[nodiscard]] double distance(const Point& second) const;
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    void print() const;
private:
    double x_;
    double y_;
};

#endif //POINT_HPP
