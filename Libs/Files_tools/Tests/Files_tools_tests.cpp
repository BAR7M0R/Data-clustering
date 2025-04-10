/******************************************************************************
 * Copyright 2025, Bartłomiej Głodek
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#include "Files_tools.hpp"
#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>

TEST_CASE("FileParser handles valid input correctly", "[FileParser]") {
    std::filesystem::path testFilePath = "..\\Data\\test_data.txt";
    std::ofstream testFile(testFilePath);
    if (!testFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    testFile << "0.97903473 6.89791050\n"
                "0.96688149 7.55303680\n"
                "0.85681183 7.32321570\n"
                "0.41846709 6.72656940\n"
                "0.70438257 7.42043560\n"
                "0.85114891 7.18602620\n"
                "0.76367192 6.67723220\n"
                "0.47939162 7.35907910\n"
                "0.91760684 6.39835690\n"
                "1.89344300 7.07566790\n"
                "1.13768190 7.59285360\n"
                "0.70938180 6.55385450\n"
                "0.87237557 6.73823860\n"
                "1.26879200 6.59996020\n"
                "1.17184180 7.08950590\n"
                "1.28625000 6.43205550\n"
                "1.69048630 6.97017530\n"
                "0.57739984 6.50003780\n"
                "1.04858640 7.00144420\n"
                "0.80360814 6.99530930\n";
    testFile.close();

    //REQUIRE_NOTHROW(FileParser(testFilePath));
    Data testData = FileParser(testFilePath);
    REQUIRE(testData.size() == 20);
    REQUIRE(testData.get()[0] == Point(0.97903473, 6.89791050));
    REQUIRE(testData.get()[1] == Point(0.96688149, 7.55303680));
    REQUIRE(testData.get()[2] == Point(0.85681183, 7.32321570));
}

TEST_CASE("FileParser throws exception on invalid file", "[FileParser]") {
    REQUIRE_THROWS_AS(FileParser("non_existent.txt"), std::runtime_error);
}