// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <filesystem>
#include <matplot/matplot.h>
#include "Point.hpp"
#include "Data.hpp"
#include "CrispClustering.hpp"
#include "FuzzyClustering.hpp"
#include "Files_tools.hpp"
#include "Ploting_tools.hpp"
namespace fs = std::filesystem;

int main()
{
    fs::path filePathDC = "..\\data\\DC-Data4.txt";
    fs::path filePathDCN = "..\\data\\DCN-Data4.txt";
    //fs::path testPath = "..\\src\\test.txt";
    const Data DC(FileParser(filePathDC));
    const Data DCN(FileParser(filePathDCN));
    //const data testD(dRead(testPath));

    CrispClustering dataSetDCCrisp(DC.get(), 2, 2);
    CrispClustering dataSetDCNCrisp(DCN.get(), 2, 5);
    FuzzyClustering dataSetDCFuzzy(DC.get(), 2, 2, 2);
    FuzzyClustering dataSetDCNFuzzy(DCN.get(), 3, 5, 5);

    matplot::tiledlayout();
    Ploting(std::vector<Data>({DC}), "DC row data");
    Ploting(std::vector<Data>({DCN}), "DC row data");
    Ploting(dataSetDCCrisp.getClusters(), "dataSetDCCrisp");
    Ploting(dataSetDCNCrisp.getClusters(), "dataSetDCNCrisp");
    Ploting(dataSetDCFuzzy.getClusters(), "dataSetDCFuzzy");
    Ploting(dataSetDCNFuzzy.getClusters(), "dataSetDCNFuzzy");

    matplot::show();
}
