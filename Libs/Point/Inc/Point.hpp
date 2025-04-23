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

#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:
    Point() = default;
    Point(double x, double y);
    Point(double xMin, double xMax, double yMin, double yMax);
    Point& operator=(const Point& other) = default;
    Point& operator+=(const Point& p);
    bool operator==(const Point& p) const;
    [[nodiscard("point::operator+")]] Point operator+(const Point& p) const;
    [[nodiscard("point::operator-")]] Point operator-(const Point& p) const;
    [[nodiscard("point::operator*")]] Point operator*(double mul) const;
    [[nodiscard("point::operator//")]] Point operator/(double dev) const;
    [[nodiscard("point::distance")]] double distance(const Point& second) const;
    [[nodiscard("point::getX")]] auto getX() const -> double;
    [[nodiscard("point::getY")]] auto getY() const -> double;
    [[nodiscard("point::getX_ref")]] auto getX_ref() -> double&;
    const double &getX_ref() const;
    [[nodiscard("point::getY_ref")]] auto getY_ref() -> double&;
    const double &getY_ref() const;
    [[nodiscard("point::get")]] auto get() const -> Point;

    void print() const;
    static bool checkIfFirstXGreater(const Point &first, const Point &second);
    static bool checkIfFirstYGreater(const Point &first, const Point &second);
    static bool checkIfFirstXSmaller(const Point &first, const Point &second);
    static bool checkIfFirstYSmaller(const Point &first, const Point &second);
private:
    double x_ = 0.0;
    double y_ = 0.0;


};

#endif //POINT_HPP
