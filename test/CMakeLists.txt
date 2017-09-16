cmake_minimum_required(VERSION 2.8)

if(CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_FLAGS "-std=c++11")
elseif(NOT CMAKE_CXX_STANDARD) # don't override c++ standard if already set
    set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(is_detected_test is_detected_test.cpp)
target_link_libraries(is_detected_test jakalib)
add_test(is_detected_test_case is_detected_test)

add_executable(variant_test variant_test.cpp)
target_link_libraries(variant_test jakalib)
add_test(variant_test_case variant_test)

add_executable(optional_test optional_test.cpp)
target_link_libraries(optional_test jakalib)
add_test(optional_test optional_test)

#add_executable(test_type_traits test_type_traits.cpp)
#target_link_libraries(test_type_traits jakalib)
#add_test(test_type_traits test_type_traits)

