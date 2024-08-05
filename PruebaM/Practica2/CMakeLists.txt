cmake_minimum_required(VERSION 3.10)
project(MImTwo)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(MImTwo MImTwo.cpp)
target_link_libraries(MImTwo ${OpenCV_LIBS})

