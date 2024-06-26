// Data clustering.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <matplot/matplot.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>

namespace fs = std::filesystem;

class point
{
public:
    point()
        : x_(0)
        , y_(0)
    {}
    point(const double &x, const double &y)
        : x_(x)
        , y_(y)
    {}
    point(const point &p)
        : x_(p.x_)
        , y_(p.y_)
    {}
    point &operator=(const point &p) {
        if (this != &p) {
            x_ = p.x_;
            y_ = p.y_;
        }
        return *this;
    }
    point operator*(const double &mul)
    {
        x_ *= mul;
        y_ *= mul;
        return *this;
    }
    point &operator+(const point& p)
    {
        if (this != &p) {
            x_ += p.x_;
            y_ += p.y_;
        }
        return *this;
    }
    point& operator-(const point& p)
    {
        if (this != &p) {
            x_ -= p.x_;
            y_ -= p.y_;
        }
        return *this;
    }
    double getX() const
    {
        return x_;
    }
    double getY() const
    {
        return y_;
    }
    void print() const
    {
        std::cout << "x: " << x_ << "y: " << y_ << "\n";
    }
private:
    double x_;
    double y_;
};

class data
{
public:
    data(const std::vector<point>& data)
        :data_(data)
    {
    }
    std::vector<double> getX() const
    {
        std::vector<double> X;
        std::transform(data_.begin(), data_.end(), std::back_inserter(X), [](point data) {return data.getX(); });
        return X;
    }
    std::vector<double> getY() const
    {
        std::vector<double> Y;
        std::transform(data_.begin(), data_.end(), std::back_inserter(Y), [](point data) {return data.getY(); });
        return Y;
    }
    std::vector<point> get() const
    {
        return data_;
    }
    size_t size()
    {
        return(data_.size());
    }
    void printData() const
    {
        for (auto p : data_)
        {
            p.print();
        }
    }
protected:
    void set(const std::vector<point>& data)
    {
        data_ = data;
    }
private:
    std::vector<point> data_;
};

class crispClustering : public data
{
    using matrixU = std::vector<std::vector<double>>;
    using matrixP = std::vector<point>;
public:
    /// <summary>
    /// constructor to calculate crisp clustering it is doing all work for you...
    /// </summary>
    /// <param name="rowData">set of points</param>
    /// <param name="numberOfClusters">number of clusters</param>
    /// <param name="calculationDepth">max number of repetition of gruping</param>
    crispClustering(const std::vector<point>& rowData, const size_t &numberOfClusters, const size_t &calculationDepth)
        : data(rowData)
        , numberOfClusters_(numberOfClusters)
        , previous_(initU())
    {

    }

private:
    matrixU initU()
    {
        matrixU temp;
        temp.resize(size(), std::vector<double>(numberOfClusters_, 0));

        size_t counter(0);
        for (size_t i(0); i < temp.size(); ++i)
        {

            for (size_t j(0); j < numberOfClusters_; ++j)
            {
                if ((j & numberOfClusters_) == 0 and j != 0 and i != 0)
                {
                    ++counter;
                }
                if (j == (((i - counter) % numberOfClusters_)))
                {
                    temp.at(i).at(j) = 1;
                }
            }
        }
        return temp;
    }
    matrixP calculePrototypes(const matrixU& currentMatrixU)
    {
        matrixP temp;
        temp.resize(numberOfClusters_, point(0,0));
        for (size_t i(0); i < temp.size(); ++i)
        {
            
        }
        return temp;
    }
    const size_t numberOfClusters_;
    matrixU previous_;
    matrixU next_;
};
static data dRead(fs::path& path)
{
    std::fstream inputFile(path);
    std::vector<point> formatedData;
    std::string line;

    if (!inputFile.is_open()) {
        throw std::runtime_error("filed to read selected file");
    }
    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }
        std::istringstream iss(line);
        double value1, value2;
        iss >> value1 >> value2;
        formatedData.push_back(point(value1, value2));
    }
    return data(formatedData);
}

int main()
{
    fs::path filePathDC = "C:\\Users\\Studia\\source\\repos\\Data clustering\\Data clustering\\DC-Data4.txt";
    fs::path filePathDCN = "C:\\Users\\Studia\\source\\repos\\Data clustering\\Data clustering\\DCN-Data4.txt";
    const data DC(dRead(filePathDC));
    const data DCN(dRead(filePathDCN));
    crispClustering dataSetDC(DC.get(), 3, 13);
    crispClustering dataSetDCN(DCN.get(), 3, 13);

    matplot::figure();
    matplot::hold(matplot::on);
    matplot::scatter(DC.getX(), DC.getY());
    //matplot::scatter(DCN.getX(), DCN.getY());


    matplot::show();
}
