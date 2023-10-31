cmake_minimum_required(VERSION 3.10)
project(GolombCodingTests)

find_package(Catch2 REQUIRED)

add_executable(unit_tests unit_tests.cpp Golomb.cpp Golomb_Decoder.cpp GolombDecoder.hpp Golomb_Enconder.cpp GolombEncoder.hpp  BitStreamWithPosition.h)

target_link_libraries(unit_tests Catch2::Catch2)

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
