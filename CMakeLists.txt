cmake_minimum_required(VERSION 3.6)
project(HyperCSV)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${cpp} ${hpp})

file(GLOB source_list "*.cpp" "*.hpp")

add_executable(HyperCSV ${source_list})
