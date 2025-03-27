//
// Created by Dell on 10/03/2025.
//

#include "Ploting_tools.hpp"
#include <catch2/catch_test_macros.hpp>
#include <matplot/freestanding/plot.h>
#include <limits>
TEST_CASE("Ploting tools", "[ploting tools]") {
    SECTION("sizer normal functionality")
    {
        struct testDataStruct{
            std::pair<std::uint8_t, std::uint8_t> subplotSize;
            std::size_t plotNumber;
            std::pair<std::uint8_t, std::uint8_t> outputSize;
        };
        std::vector<testDataStruct> testData
        {
            {{1,1},{2},{2,1}},
            {{1,1},{3},{2,2}},
            {{1,1},{4},{2,2}},
            {{1,1},{5},{3,2}},
            {{1,1},{6},{3,2}},
            {{1,1},{7},{3,3}},
            {{1,1},{8},{3,3}},
            {{1,1},{9},{3,3}},
            {{1,1},{10},{4,3}},
            {{1,1},{11},{4,3}},
            {{1,1},{12},{4,3}},
            {{1,1},{13},{4,4}},
            {{1,1},{14},{4,4}},
            {{1,1},{15},{4,4}},
            {{2,1},{2},{2,1}},
            {{2,1},{3},{2,2}},
            {{2,1},{4},{2,2}},
            {{2,1},{5},{3,2}},
            {{2,1},{6},{3,2}},
            {{2,1},{7},{3,3}},
            {{2,1},{8},{3,3}},
            {{2,1},{9},{3,3}},
            {{2,1},{10},{4,3}},
            {{2,1},{11},{4,3}},
            {{2,1},{12},{4,3}},
            {{2,1},{13},{4,4}},
            {{2,1},{14},{4,4}},
            {{2,1},{15},{4,4}},
        };
        for (auto&[subplotSize, plotNumber, outputSize]: testData) {
            auto [fst, snd] = Sizer(subplotSize, plotNumber);
            CAPTURE(subplotSize.first, subplotSize.second, plotNumber, outputSize.first, outputSize.second, fst, snd);
            REQUIRE(fst == outputSize.first);
            REQUIRE(snd == outputSize.second);
        }
    }

}
