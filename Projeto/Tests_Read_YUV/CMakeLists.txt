cmake_minimum_required(VERSION 3.10)
project(GolombInterframeCodingTests)

find_package(Catch2 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories()
add_executable(main main.cpp)


target_link_libraries(main)

enable_testing()
add_test(NAME main COMMAND main)