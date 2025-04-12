add_library(Data_tools STATIC Src/Data_tools.cpp)
target_compile_features(Data_tools PUBLIC cxx_std_20)
target_include_directories(Data_tools PUBLIC Inc)
target_link_libraries(Data_tools PRIVATE Linspain)