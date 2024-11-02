cmake_minimum_required(VERSION 3.16)
project(treesitter_cpp_test)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake")

find_package(PkgConfig)
pkg_search_module(TREE_SITTER REQUIRED tree-sitter)
find_package(tree-sitter-json)
message("found tree-sitter: ${TREE_SITTER_LIBRARIES}")
message("found tree-sitter-json:  ${TREE_SITTER_JSON_LIBRARIES}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(TREE_SITTER_JSON_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree_sitter_json_test.cpp
  )

add_executable(tree_sitter_json_test)
target_sources(tree_sitter_json_test
 PRIVATE
  ${TREE_SITTER_JSON_TEST_SOURCES}
)
target_include_directories(tree_sitter_json_test
 PRIVATE
  ${TREE_SITTERINCLUDE_DIRS}
)

target_link_libraries(tree_sitter_json_test
  ${TREE_SITTER_LIBRARIES}
  ${TREE_SITTER_JSON_LIBRARIES}
)
