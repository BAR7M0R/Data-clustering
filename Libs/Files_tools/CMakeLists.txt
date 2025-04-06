add_library(Files_tools STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Src/Files_tools.cpp)
target_compile_features(Files_tools PUBLIC cxx_std_20)
target_include_directories(Files_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(Files_tools PRIVATE Point Data)