//
// Created by Dell on 10/03/2025.
//

#ifndef DATA_HPP
#define DATA_HPP
#include <vector>
#include "Point.hpp"

class Data
{
public:
    explicit Data(const std::vector<Point>& rangeOfData);
    [[nodiscard]] std::vector<double> getX() const;
    [[nodiscard]] std::vector<double> getY() const;
    [[nodiscard]] std::vector<Point> get() const;
    [[nodiscard]] size_t size() const;
protected:
    void set(const std::vector<Point>& data);
private:
    std::vector<Point> data_;
};


#endif //DATA_HPP
