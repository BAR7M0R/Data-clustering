include(AddCatch2)

add_executable(
        uint_tests
        Point_test.cpp
        Data_test.cpp
        CrispClustering_test.cpp
        FuzzyClustering_test.cpp
)
target_link_libraries(
        uint_tests PRIVATE main Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

catch_discover_tests(unit_tests)
