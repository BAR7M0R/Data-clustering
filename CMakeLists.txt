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
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Point Data CrispClustering FuzzyClustering)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE Matplot++::cimg  Matplot++::matplot)
