cmake_minimum_required(VERSION 3.6.3)

add_executable(is_detected_test is_detected_test.cpp)
target_link_libraries(is_detected_test jakalib)
add_test(is_detected_test_case is_detected_test)

add_executable(variant_test variant_test.cpp)
target_link_libraries(variant_test jakalib)
add_test(variant_test_case variant_test)
