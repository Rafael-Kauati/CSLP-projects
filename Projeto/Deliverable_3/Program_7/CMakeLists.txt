cmake_minimum_required(VERSION 3.10)
project(GolombCodingTests)

find_package(Catch2 REQUIRED)

add_executable(unit_tests tests/unit_tests.cpp ../Program_6/Golomb_Decoder.cpp ../Program_6/GolombDecoder.hpp ../Program_6/Golomb_Enconder.cpp ../Program_6/GolombEncoder.hpp)

target_link_libraries(unit_tests Catch2::Catch2)

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
