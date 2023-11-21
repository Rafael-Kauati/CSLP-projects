cmake_minimum_required(VERSION 3.10)
project(GolombCodingTests)

find_package(Catch2 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(unit_tests unit_tests.cpp Golomb.cpp Golomb_Encoder.cpp Golomb_Encoder.hpp  Golomb_Decoder.cpp Golomb_Decoder.hpp BitStream.h)

target_link_libraries(unit_tests Catch2::Catch2 ${OpenCV_LIBS})

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
