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
    fs::path filePathDC = "..\\DData\\DC-Data4.txt";
    fs::path filePathDCN = "..\\DData\\DCN-Data4.txt";

    const Data DC(FileParser(filePathDC));
    const Data DCN(FileParser(filePathDCN));

    CrispClustering datasetDCCrisp(DC.get(), 2, 2);
    CrispClustering datasetDCNCrisp(DCN.get(), 2, 5);
    FuzzyClustering datasetDCFuzzy(DC, 2, 2);
    FuzzyClustering datasetDCNFuzzy(DCN, 3, 2);
    FuzzyClustering datasetDCNFuzzy2(DCN, 2, 2);
    FuzzyClustering datasetDCNFuzzy23(DCN, 3, 3);
    FuzzyClustering datasetDCNFuzzy215(DCN, 3, 1.5);
    auto [dataDC, membersDC, centroidsDC] = datasetDCFuzzy.get();
    auto [dataDCN, membersDCN, centroidsDCN] = datasetDCNFuzzy.get();
    auto [dataDCN2, membersDCN2, centroidsDCN2] = datasetDCNFuzzy2.get();
    auto [dataDCN23, membersDCN23, centroidsDCN23] = datasetDCNFuzzy23.get();
    auto [dataDCN215, membersDCN215, centroidsDCN215] = datasetDCNFuzzy215.get();
    matplot::tiledlayout();
    Ploting(std::vector<Data>({DC}), "DC row Data");
    Ploting(std::vector<Data>({DCN}), "DC row Data");
    Ploting(datasetDCCrisp.getClusters(), "dataSetDCCrisp");
    Ploting(datasetDCNCrisp.getClusters(), "dataSetDCNCrisp");
    Ploting(dataDC, membersDC, centroidsDC, "dataSetDCFuzzy");
    Ploting(dataDCN, membersDCN, centroidsDCN, "dataSetDCNFuzzy clusters:3 fuzzyfactor: 2");
    Ploting(dataDCN2, membersDCN2, centroidsDCN2, "dataSetDCNFuzzy clusters:2 fuzzyfactor: 2");
    Ploting(dataDCN23, membersDCN23, centroidsDCN23, "dataSetDCNFuzzy clusters:3 fuzzyfactor: 1.5");
    Ploting(dataDCN215, membersDCN215, centroidsDCN215, "dataSetDCNFuzzy clusters:3 fuzzyfactor: 3");
    matplot::show();
}
