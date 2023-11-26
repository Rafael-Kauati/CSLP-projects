cmake_minimum_required(VERSION 3.10)
project(GolombCodingTests)

find_package(Catch2 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(unit_tests unit_tests.cpp
                Golomb/Golomb.cpp 
                Golomb/Golomb_Encoder.cpp 
                Golomb/Golomb_Encoder.hpp 
                Golomb/Golomb_Decoder.cpp 
                Golomb/Golomb_Decoder.hpp
                Predictor/BitStream.h
                Predictor/Frame_Predicter.h)

target_link_libraries(unit_tests Catch2::Catch2 ${OpenCV_LIBS})

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
