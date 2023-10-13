cmake_minimum_required(VERSION 3.10)
project(GolombCodingTests)

find_package(Catch2 REQUIRED)

add_executable(GolombCodingTests Tests.cpp Golomb_Decoder.cpp GolombDecoder.hpp Golomb_Enconder.cpp GolombEncoder.hpp)

target_link_libraries(GolombCodingTests Catch2::Catch2)

enable_testing()
add_test(NAME GolombCodingTests COMMAND GolombCodingTests)
