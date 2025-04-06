cmake_minimum_required(VERSION 3.5)

project(data_clustering
        VERSION 0.5.0
        LANGUAGES CXX)

enable_testing()

set(CMAKE_PREFIX_PATH "C:/Users/Dell/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Matplot++ CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)

add_subdirectory(Libs/Point)
add_subdirectory(Libs/Data)
add_subdirectory(Libs/Files_tools)
add_subdirectory(Libs/Ploting_tools)

add_library(CrispClustering STATIC Src/CrispClustering.cpp)
target_compile_features(CrispClustering PUBLIC cxx_std_20)
target_include_directories(CrispClustering PUBLIC Inc)
target_link_libraries(CrispClustering PRIVATE Point Data)

add_library(FuzzyClustering STATIC Src/FuzzyClustering.cpp)
target_compile_features(FuzzyClustering PUBLIC cxx_std_20)
target_include_directories(FuzzyClustering PUBLIC Inc)
target_link_libraries(FuzzyClustering PRIVATE Point Data)

add_executable(my_tests
        Tests/CrispClustering_tests.cpp
        Tests/FuzzyClustering_tests.cpp
        Libs/Data/Tests/Data_tests.cpp
        Libs/Point/Tests/Point_tests.cpp
        Libs/Files_tools/Tests/Files_tools_tests.cpp
        Libs/Ploting_tools/Tests/Ploting_tools_tests.cpp)

target_compile_features(my_tests PRIVATE cxx_std_20)
target_include_directories(my_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(my_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(my_tests PRIVATE Point)
target_link_libraries(my_tests PRIVATE Data)
target_link_libraries(my_tests PRIVATE FuzzyClustering)
target_link_libraries(my_tests PRIVATE CrispClustering)
target_link_libraries(my_tests PRIVATE Files_tools)
target_link_libraries(my_tests PRIVATE Ploting_tools)

include(CTest)
include(Catch)
catch_discover_tests(my_tests)

add_executable(my_app main.cpp)
target_compile_features(my_app PRIVATE cxx_std_20)
target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(my_app PRIVATE Point)
target_link_libraries(my_app PRIVATE Data)
target_link_libraries(my_app PRIVATE CrispClustering)
target_link_libraries(my_app PRIVATE FuzzyClustering)
target_link_libraries(my_app PRIVATE Files_tools)
target_link_libraries(my_app PRIVATE Ploting_tools)
target_link_libraries(my_app PRIVATE Matplot++::cimg  Matplot++::matplot)

