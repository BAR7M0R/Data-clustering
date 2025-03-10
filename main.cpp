// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <matplot/matplot.h>
#include <filesystem>
#include <fstream>
#include <vector>

#include <utility>


#include "src/Point.hpp"
#include "src/data.hpp"

namespace fs = std::filesystem;

static Data dRead(fs::path& path)
{
    std::fstream inputFile(path);
    std::vector<Point> formatedData;
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
        formatedData.push_back(Point(value1, value2));
    }
    return Data(formatedData);
}


void ploting(Data frist, std::vector<Data> second, std::string& plotTitle)
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
    //matplot::subplot()
    matplot::hold(matplot::on);
    for (size_t clusterIndex(0); clusterIndex < 2; ++clusterIndex)
    {
        Data dataToPrint = second.at(clusterIndex);
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
    const Data DC(dRead(filePathDC));
    const Data DCN(dRead(filePathDCN));
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
