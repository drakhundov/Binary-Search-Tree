cmake_minimum_required(VERSION 3.16)
project(binary_search_tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(bst_lib
        src/BST/BST.cpp
        src/BST/BST_node.cpp
)

target_include_directories(bst_lib PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(bst_main
        src/main.cpp
)
target_link_libraries(bst_main PRIVATE bst_lib)

add_executable(bst_unittests
        src/unittest/test_BST.cpp
)
target_link_libraries(bst_unittests PRIVATE bst_lib)
