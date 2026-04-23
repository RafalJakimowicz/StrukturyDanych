cmake_minimum_required(VERSION 3.10)
project(data_structures CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(data_structures_lib INTERFACE)
target_include_directories(data_structures_lib INTERFACE include/)

add_executable(efficency_test 
    src/main.cpp)
target_link_libraries(efficency_test PRIVATE
    data_structures_lib)

enable_testing()
add_subdirectory(tests)