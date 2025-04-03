// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>

#include <matplot/matplot.h>

#include "Data.hpp"
#include "CrispClustering.hpp"
#include "FuzzyClustering.hpp"
#include "Files_tools.hpp"
#include "Ploting_tools.hpp"

namespace fs = std::filesystem;

int main()
{
    std::cout.flush();
    fs::path filePathDC = "..\\data\\DC-Data4.txt";
    fs::path filePathDCN = "..\\data\\DCN-Data4.txt";
    //fs::path testPath = "..\\src\\test.txt";
    const Data DC(FileParser(filePathDC));
    const Data DCN(FileParser(filePathDCN));
    //const data testD(dRead(testPath));
    //const Data test(std::vector<Point>({{1.,8.}, {3.,8.},{1.,6.}, {3.,6.}, {8.,1.}, {8.,3.},{6.,1.}, {6.,3.}}));
    CrispClustering datasetDCCrisp(DC.get(), 2, 2);
    CrispClustering datasetDCNCrisp(DCN.get(), 2, 5);
    FuzzyClustering datasetDCFuzzy(DC, 2, 2);
    FuzzyClustering datasetDCNFuzzy(DCN, 3, 2);

    auto [a, b, c] = datasetDCNFuzzy.get();
    a.print();
    for (auto bp: b) {
        std::cout << "next group\n";
        for (auto bpp: bp) {
            std::cout << (bpp > 0.5) << " " << bpp << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "centers\n";
    for (auto cp :c)
    {
        cp.print();
    }
    //matplot::tiledlayout();
    //Ploting(std::vector<Data>({DC}), "DC row data");
    //Ploting(std::vector<Data>({DCN}), "DC row data");
    //Ploting(datasetDCCrisp.getClusters(), "dataSetDCCrisp");
    //Ploting(datasetDCNCrisp.getClusters(), "dataSetDCNCrisp");
    //Ploting(dataSetDCFuzzy.getClusters(), "dataSetDCFuzzy");
    //Ploting(dataSetDCNFuzzy.getClusters(), "dataSetDCNFuzzy");

    //matplot::show();
}
