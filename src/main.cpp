// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <matplot/matplot.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <cmath>

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
    point &operator+=(const point& p)
    {
        if (this != &p)
        {
            x_ += p.x_;
            y_ += p.y_;
        }
        return *this;
    }
    point operator+(const point& p)
    {
        if (this != &p) 
        {
            point temp(*this);
            temp.x_ += p.x_;
            temp.y_ += p.y_;
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
    point& operator/(const double& dev)
    {
        if (dev == 0)
        {
            throw std::invalid_argument("0 devision");
        }
        x_ /= dev;
        y_ /= dev;
        return *this;
    }
    double distance(const point& second) const
    {
        return sqrt(pow(x_ - second.x_, 2) + pow(y_ - second.y_, 2));
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
    std::vector<point>get() const
    {
        return data_;
    }
    size_t size()
    {
        return(data_.size());
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
    using cluster = std::vector<point>;
public:
    /// <summary>
    /// constructor to calculate crisp clustering it is doing all work for you...
    /// </summary>
    /// <param name="rowData">set of points</param>
    /// <param name="numberOfClusters">number of clusters</param>
    /// <param name="calculationDepth">max number of repetition of gruping</param>
    crispClustering(const std::vector<point>& rowData, const size_t& numberOfClusters, const size_t& calculationDepth)
        : data(rowData)
        , numberOfClusters_(numberOfClusters)
        , calculationDepth_(calculationDepth)
        , previous_(initU())
    {
        for (size_t depthIndex(0); depthIndex < calculationDepth_; ++depthIndex)
        {
            next_.resize(size(), std::vector<double>(numberOfClusters_, 0));
            matrixP currentPrototypes = calculePrototypes(previous_);
            std::vector<double> distances;
            for (size_t pIndex(0); pIndex < size(); ++pIndex)
            {
                for (size_t vIndex(0); vIndex < numberOfClusters_; ++vIndex)
                {
                    distances.push_back(currentPrototypes.at(vIndex).distance(get().at(pIndex)));
                }
                size_t selectedCluster = std::distance(distances.begin(), std::min_element(distances.begin(), distances.end()));
                next_.at(pIndex).at(selectedCluster) = 1;
                distances.clear();
            }
            previous_ = next_;
            next_.clear();
        }
        data rawPoints(get());
        cluster tempCluster;
        for (size_t clusterIndex(0); clusterIndex < numberOfClusters_; ++clusterIndex)
        {
            for (size_t pointIndex(0); pointIndex < size(); ++pointIndex)
            {
                if (previous_.at(pointIndex).at(clusterIndex) == 1)
                {
                    tempCluster.push_back(get().at(pointIndex));
                }
            }
            clusters_.push_back(tempCluster);
            tempCluster.clear();
        }
    }
    std::vector<data> &getClusters()
    {
        return clusters_;
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
                if (j == counter)
                {
                    temp.at(i).at(j) = 1;
                }
            }
            ++counter;
            if (counter >= numberOfClusters_)
            {
                counter = 0;
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
            point tempPoint(0,0);
            double tempValue(0);
            for (size_t j(0); j < size(); ++j)
            {
                tempValue += currentMatrixU.at(j).at(i);
                tempPoint += get().at(j)*currentMatrixU.at(j).at(i);
            }
            temp.at(i) = tempPoint / tempValue;
        }
        return temp;
    }
    const size_t numberOfClusters_;
    const size_t calculationDepth_;
    matrixU previous_;
    matrixU next_;
    std::vector<data> clusters_;
};
class fuzzyClustering : public data
{
    using matrixU = std::vector<std::vector<double>>;
    using matrixP = std::vector<point>;
    using cluster = std::vector<point>;
public:
    /// <summary>
    /// constructor to calculate crisp clustering it is doing all work for you...
    /// </summary>
    /// <param name="rowData">set of points</param>
    /// <param name="numberOfClusters">number of clusters</param>
    /// <param name="calculationDepth">max number of repetition of gruping</param>
    fuzzyClustering(const std::vector<point> &rowData, const size_t &numberOfClusters, const double &fuzzyfyingFactor, const size_t &calculationDepth)
        : data(rowData)
        , numberOfClusters_(numberOfClusters)
        , calculationDepth_(calculationDepth)
        , fuzzyfyingFactor_(fuzzyfyingFactor)
        , previous_(initU())
    {
        for (size_t depthIndex(0); depthIndex < calculationDepth_; ++depthIndex)
        {
            next_.resize(size(), std::vector<double>(numberOfClusters_, 0));
            matrixP currentPrototypes = calculePrototypes(previous_);
            std::vector<double> distances;
            for (size_t pointIndex(0); pointIndex < size(); ++pointIndex)
            {

                for (size_t assignedClusterIndex(0); assignedClusterIndex < numberOfClusters_; ++assignedClusterIndex)
                {
                    double assignedClusterDistance = get().at(pointIndex).distance(currentPrototypes.at(assignedClusterIndex));
                    assignedClusterDistance = pow(assignedClusterDistance, (-2.) / (fuzzyfyingFactor_ - 1));
                    double totalDistances = 0;
                    for (size_t clusterIndex(0); clusterIndex < numberOfClusters_; ++clusterIndex)
                    {
                        double tempDistance = get().at(pointIndex).distance(currentPrototypes.at(clusterIndex));
                        tempDistance = pow(tempDistance, (-2.) / (fuzzyfyingFactor_ - 1));
                        totalDistances += tempDistance;
                    }
                    next_.at(pointIndex).at(assignedClusterIndex) = assignedClusterDistance / totalDistances;
                }

            }
            previous_ = next_;
            next_.clear();
            for (auto i : previous_)
            {
                for (auto j : i)
                    std::cout << j << " ";
                std::cout << std::endl;
            }

        }
        data rawPoints(get());
        cluster tempCluster;
        for (size_t clusterIndex(0); clusterIndex < numberOfClusters_; ++clusterIndex)
        {
            for (size_t pointIndex(0); pointIndex < size(); ++pointIndex)
            {
                if (previous_.at(pointIndex).at(clusterIndex) >= .5)
                {
                    tempCluster.push_back(get().at(pointIndex));
                }
            }
            clusters_.push_back(tempCluster);
            tempCluster.clear();
        }
    }
    std::vector<data>& getClusters()
    {
        return clusters_;
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
                if (j == counter)
                {
                    temp.at(i).at(j) = 1;
                }
            }
            ++counter;
            if (counter >= numberOfClusters_)
            {
                counter = 0;
            }
        }
        return temp;
    }
    matrixP calculePrototypes(const matrixU& currentMatrixU)
    {
        matrixP temp;
        temp.resize(numberOfClusters_, point(0, 0));
        for (size_t i(0); i < temp.size(); ++i)
        {
            point tempPoint(0, 0);
            double tempValue(0);
            for (size_t j(0); j < size(); ++j)
            {
                tempValue += currentMatrixU.at(j).at(i);
                tempPoint += get().at(j) * currentMatrixU.at(j).at(i);
            }
            temp.at(i) = tempPoint / tempValue;
        }
        return temp;
    }
    const size_t numberOfClusters_;
    const size_t calculationDepth_;
    const double fuzzyfyingFactor_;
    matrixU previous_;
    matrixU next_;
    std::vector<data> clusters_;
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
void ploting(data frist, std::vector<data> second, std::string& plotTitle)
{
    static uint8_t numberOfPlots = 0;
    numberOfPlots++;
    static uint8_t plotsInRow=1;
    static uint8_t plotsInCol = 1;
    if (numberOfPlots >= plotsInRow * plotsInCol)
    {

    }
    matplot::figure();
    matplot::scatter(frist.getX(), frist.getY());
    matplot::figure();
    matplot::subplot()
    matplot::hold(matplot::on);
    for (size_t clusterIndex(0); clusterIndex < 2; ++clusterIndex)
    {
        data dataToPrint = second.at(clusterIndex);
        matplot::scatter(dataToPrint.getX(), dataToPrint.getY());
    }
    matplot::hold(matplot::off);
}
template <typename T>
concept Number = std::integral<T>;

template<Number T1, Number T2>
std::pair<T1, T1> sizer(std::pair<T1, T1> subplotSize, const T2 plotNumber)
{
    if (plotNumber > subplotSize.first * subplotSize.second)
    {
        if (plotNumber%subplotSize.first == 0)
        {
            ++subplotSize.first;
        }
        if (plotNumber-subplotSize.first%subplotSize.second == 0) {
            ++subplotSize.second;
        }
        return sizer(subplotSize, plotNumber);
    }
    else
    {
        return subplotSize;
    }
}
int main()
{
    fs::path filePathDC = "..\\src\\DC-Data4.txt";
    fs::path filePathDCN = "..\\src\\DCN-Data4.txt";
    //fs::path testPath = "..\\src\\test.txt";
    const data DC(dRead(filePathDC));
    const data DCN(dRead(filePathDCN));
    //const data testD(dRead(testPath));

    crispClustering dataSetDCCrisp(DC.get(), 2, 2);
    crispClustering dataSetDCNCrisp(DCN.get(), 2, 5);
    fuzzyClustering dataSetDCFuzzy(DC.get(), 2, 2, 2);
    fuzzyClustering dataSetDCNFuzzy(DCN.get(), 2, 2, 5);

    ploting(DC, dataSetDCCrisp.getClusters());
    ploting(DCN, dataSetDCNCrisp.getClusters());
    ploting(DC, dataSetDCFuzzy.getClusters());
    ploting(DCN, dataSetDCNFuzzy.getClusters());
    matplot::show();
    std::cout << "halo grarzynka lecimy z tematem" << "\n";
}
