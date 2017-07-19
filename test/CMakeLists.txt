cmake_minimum_required(VERSION 2.8)

add_executable(is_detected_test is_detected_test.cpp)
target_link_libraries(is_detected_test jakalib)

add_test(is_detected_test_case is_detected_test)
