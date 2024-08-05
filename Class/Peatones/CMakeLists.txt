cmake_minimum_required(VERSION 3.10)
project(Principal)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(Principal Principal.cpp)
target_link_libraries(Principal ${OpenCV_LIBS})

