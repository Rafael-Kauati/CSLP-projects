cmake_minimum_required(VERSION 3.10)
project(BitStreamTests)

find_package(Catch2 REQUIRED)

add_executable(unit_tests tests/unit_tests.cpp ../Program_4/BitStream.h)
add_executable(main main.cpp)

target_link_libraries(unit_tests Catch2::Catch2)

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
