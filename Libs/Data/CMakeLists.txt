add_library(Data STATIC Src/Data.cpp)
target_compile_features(Data PUBLIC cxx_std_20)
target_include_directories(Data PUBLIC Inc)
target_link_libraries(Data PUBLIC Point)
