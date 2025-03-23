//
// Created by Dell on 11/03/2025.
//

#include "ploting_tools.hpp"
#include <matplot/matplot.h>
#include <utility>


void Ploting(Data first, std::vector<Data> second, const char* plotTitle)
{
    static uint8_t numberOfPlots = 0;
    numberOfPlots++;
    static uint8_t plotsInRow=1;
    static uint8_t plotsInCol = 1;
    if (numberOfPlots >= plotsInRow * plotsInCol)
    {

    }
    matplot::figure();
    matplot::scatter(first.getX(), first.getY());
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

template<typename T1>
std::pair<T1, T1> sizer(std::pair<T1, T1> subplotSize, const std::size_t plotNumber)
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