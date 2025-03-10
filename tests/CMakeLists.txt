include(AddCatch2)

add_executable(
        uint_tests
        test_calc.cpp
)
target_link_libraries(
        uint_tests PRIVATE main Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

catch_discover_tests(unit_tests)
