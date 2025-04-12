add_library(Ploting_tools STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Src/Ploting_tools.cpp)
target_compile_features(Ploting_tools PUBLIC cxx_std_20)
target_include_directories(Ploting_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(Ploting_tools PRIVATE Data Matplot++::cimg  Matplot++::matplot)
