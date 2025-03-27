//
// Created by Dell on 11/03/2025.
//

#include "files_tools.hpp"
#include "Data.hpp"
#include <fstream>
#include <sstream>

Data FileParser(const std::filesystem::path& file)
{
    std::ifstream inputFile(file);
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
        formatedData.emplace_back(value1, value2);
    }
    return Data(formatedData);
}