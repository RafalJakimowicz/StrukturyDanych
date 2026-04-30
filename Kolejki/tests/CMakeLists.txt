include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)
FetchContent_MakeAvailable(Catch2)

add_executable(run_tests 
    TimSortTest.cpp
    QueueVectorTest.cpp
    QueueTreeTest.cpp
)

target_link_libraries(run_tests PRIVATE data_structures_lib Catch2::Catch2WithMain)

if(TARGET_OS STREQUAL "windows" OR WIN32)
    target_link_options(run_tests PRIVATE -static -static-libgcc -static-libstdc++)
endif()

if(NOT TARGET_OS STREQUAL "windows")
    include(Catch)
    catch_discover_tests(run_tests)
endif()