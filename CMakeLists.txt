cmake_minimum_required(VERSION 3.14)

project(data_clustering)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode - enabling tests")

    enable_testing()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

set(CMAKE_PREFIX_PATH "C:/Users/Dell/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")

add_executable(my_app main.cpp
        src/point.cpp
        src/point.hpp
        src/data.cpp
        src/data.hpp
        src/CrispClustering.cpp
        src/CrispClustering.hpp
        src/FuzzyClustering.cpp
        src/FuzzyClustering.hpp)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE Matplot++::cimg  Matplot++::matplot)
