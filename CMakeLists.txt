cmake_minimum_required(VERSION 3.6.3)
project(jakalib LANGUAGES CXX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_library(jakalib INTERFACE)
target_include_directories(jakalib INTERFACE include/)

enable_testing()
add_subdirectory(test bin)
