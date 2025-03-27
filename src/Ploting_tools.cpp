//
// Created by Dell on 11/03/2025.
//

#include "ploting_tools.hpp"
#include <matplot/matplot.h>
#include <utility>


void Ploting(Data first, std::vector<Data> second, const char* plotTitle)
{
    /*static uint8_t numberOfPlots = 0;
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
    matplot::hold(matplot::off);*/
}

std::pair<std::uint8_t, std::uint8_t> Sizer(std::pair<std::uint8_t, std::uint8_t> subplotSize, const std::size_t plotNumber)
{
    if (plotNumber > std::numeric_limits<std::uint16_t>::max()) {
        throw std::out_of_range("plotNumber is out of range");
    }
    if (plotNumber > subplotSize.first * subplotSize.second)
    {
        if (0 > static_cast<std::int16_t>(subplotSize.first - plotNumber) and 0 == subplotSize.first - subplotSize.second) {
            ++subplotSize.first;
            return Sizer(subplotSize, plotNumber);
        }
        if (plotNumber >= subplotSize.first * subplotSize.second) {
            ++subplotSize.second;
            return Sizer(subplotSize, plotNumber);
        }
    }
    return subplotSize;
}
