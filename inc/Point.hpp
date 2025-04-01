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
    Point(double xMin, double xMax, double yMin, double yMax);
    Point& operator+=(const Point& p);
    bool operator==(const Point& p) const;
    [[nodiscard("point::operator+")]] Point operator+(const Point& p) const;
    [[nodiscard("point::operator-")]] Point operator-(const Point& p) const;
    [[nodiscard("point::operator*")]] Point operator*(double mul) const;
    [[nodiscard("point::operator//")]] Point operator/(double dev) const;
    [[nodiscard("point::distance")]] double distance(const Point& second) const;
    [[nodiscard("point::getX")]] auto getX() const -> double;
    [[nodiscard("point::getY")]] auto getY() const -> double;
    [[nodiscard("point::get")]] auto get() const -> Point;



    static bool checkIfFirstXGreater(const Point &first, const Point &second);
    static bool checkIfFirstYGreater(const Point &first, const Point &second);
    static bool checkIfFirstXSmaller(const Point &first, const Point &second);
    static bool checkIfFirstYSmaller(const Point &first, const Point &second);
    void print() const;
private:
    double x_ = 0.0;
    double y_ = 0.0;
};

#endif //POINT_HPP
