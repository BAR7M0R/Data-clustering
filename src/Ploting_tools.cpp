//
// Created by Dell on 11/03/2025.
//

#include "ploting_tools.hpp"
#include <matplot/matplot.h>
#include <utility>


void Ploting(const std::vector<Data> &data, const std::string &plotTitle)
{
    static uint8_t numberOfPlots = 0;
    static std::pair<uint8_t,uint8_t> plotBox = {1,1};
    const std::vector<std::string> colors({"r", "b", "g"});
    numberOfPlots++;
    plotBox = Sizer(plotBox, numberOfPlots);

    const auto axi = matplot::nexttile();
    matplot::title(axi, plotTitle);
    uint8_t i = 0;
    for (const auto &d : data) {
        matplot::hold(matplot::on);
        const auto s = matplot::scatter(axi, d.getX(), d.getY());
        s->marker_style(".");
        s->marker_size(2);

        if (data.size() == 1) {
            s->marker_color("black");
        }
        else {
            s->marker_color(colors[i++ % colors.size()]);
        }
    }
    matplot::hold(matplot::off);


    //matplot::hold(matplot::on);
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
