cmake_minimum_required(VERSION 3.14)

project(data_clustering)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/Users/Dell/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic")

add_executable(my_app src/main.cpp)
find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE Matplot++::cimg  Matplot++::matplot)
