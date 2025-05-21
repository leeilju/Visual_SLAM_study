cmake_minimum_required(VERSION 2.8)

project(useEigen)

add_executable(useEigen src/eigenMatrix.cpp)

include_directories("/usr/include/eigen3")
