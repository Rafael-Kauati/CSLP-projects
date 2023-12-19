cmake_minimum_required(VERSION 3.10)
project(YUVfileTests)

find_package(OpenCV REQUIRED)
find_package(Catch2 REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(main main.cpp)


target_link_libraries(main Catch2::Catch2 ${OpenCV_LIBS})

enable_testing()
add_test(NAME main COMMAND main)