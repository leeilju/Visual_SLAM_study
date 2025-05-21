cmake_minimum_required(VERSION 2.8)

project(useEigen)

add_executable(eigenMatrix src/eigenMatrix.cpp)

add_executable(useGeometry src/useGeometry.cpp)

include_directories("/usr/include/eigen3")
