add_library(Data STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Src/Data.cpp)
target_compile_features(Data PUBLIC cxx_std_20)
target_include_directories(Data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(Data PUBLIC Point)