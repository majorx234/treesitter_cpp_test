# Find the native libtree-sitter-json library
#
#  TREE_SITTER_JSON_LIBRARIES   - List of libraries when using libmosquitto.
#  TREE_SITTER_JSON_FOUND       - True if libmosquitto found.

if (NOT TREE_SITTER_JSON_LIBRARY)
  find_library(
    TREE_SITTER_JSON_LIBRARY
    NAMES tree-sitter-json
    PATHS
    /usr/lib
    /usr/local/lib
  )
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
  tree-sitter-json DEFAULT_MSG
   TREE_SITTER_JSON_LIBRARY)

message(STATUS "libtree-sitter-json: ${TREE_SITTER_JSON_LIBRARY}")
set(TREE_SITTER_JSON_LIBRARIES ${TREE_SITTER_JSON_LIBRARY})

mark_as_advanced(TREE_SITTER_JSON_LIBRARY)
