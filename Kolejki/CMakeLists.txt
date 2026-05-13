cmake_minimum_required(VERSION 3.10)
project(data_structures CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_OS "linux" CACHE STRING "Target operating system: linux or windows")

add_library(data_structures_lib INTERFACE)
target_include_directories(data_structures_lib INTERFACE include/)

add_executable(efficency_test 
    src/efficency_test/EfficencyTest.cpp
    src/main.cpp)

target_compile_options(efficency_test PRIVATE -O3)
    
target_link_libraries(efficency_test PRIVATE
    data_structures_lib)

if(TARGET_OS STREQUAL "windows" OR WIN32)
    target_link_options(efficency_test PRIVATE -static -static-libgcc -static-libstdc++)
endif()

enable_testing()
add_subdirectory(tests)