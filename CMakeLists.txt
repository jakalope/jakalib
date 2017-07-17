cmake_minimum_required(VERSION 2.6)
project(jakalib)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

include_directories(include/)
add_subdirectory(test/)
