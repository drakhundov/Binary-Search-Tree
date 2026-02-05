cmake_minimum_required(VERSION 3.16)
project(binary_search_tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(bst_lib
        src/bst.cpp
)

target_include_directories(bst_lib PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(bst_unittests
        src/unittest.cpp
)
target_link_libraries(bst_unittests PRIVATE bst_lib GTest::gtest_main)
