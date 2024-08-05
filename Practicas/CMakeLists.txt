cmake_minimum_required(VERSION 3.10)
project(Practica)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(Practica Practica.cpp)
target_link_libraries(Practica ${OpenCV_LIBS})

