cmake_minimum_required(VERSION 3.10)
project(data_structures)

add_library(data_structures_lib INTERFACE)
target_include_directories(data_structures_lib INTERFACE include/)

add_executable(efficency_test 
    src/main.cpp)
target_link_libraries(efficency_test 
    data_structures_lib)