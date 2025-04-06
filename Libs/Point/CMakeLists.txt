add_library(Point STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Src/Point.cpp)
target_compile_features(Point PUBLIC cxx_std_20)
target_include_directories(Point PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)