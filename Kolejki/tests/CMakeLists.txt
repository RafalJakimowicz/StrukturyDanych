include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)
FetchContent_MakeAvailable(Catch2)


add_executable(run_tests 
    TimSortTest.cpp
)

target_link_libraries(run_tests PRIVATE data_structures_lib Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(run_tests)