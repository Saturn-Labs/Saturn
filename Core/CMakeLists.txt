cmake_minimum_required(VERSION 3.29)
project(Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
        ${INCLUDE_DIR}
        ${SOURCE_DIR}
)

file(GLOB_RECURSE API_INCLUDE_LIST
        "${INCLUDE_DIR}/*.h"
        "${INCLUDE_DIR}/*.hpp"
)

file(GLOB_RECURSE INCLUDE_LIST
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE SOURCE_LIST
        "${SOURCE_DIR}/*.cpp"
)

add_library(Core STATIC
        ${API_INCLUDE_LIST}
        ${INCLUDE_LIST}
        ${SOURCE_LIST}
)
set_target_properties(
        Core
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Core/${CMAKE_BUILD_TYPE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Core/${CMAKE_BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Core/${CMAKE_BUILD_TYPE}
)

set_target_properties(Core PROPERTIES OUTPUT_NAME "Saturn.Core")
target_precompile_headers(Core PUBLIC "${SOURCE_DIR}/pch.hpp")
find_package(Doxygen REQUIRED)

set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile)
set(DOXYGEN_OUT ${CMAKE_SOURCE_DIR}/Documentation)

# Optionally customize output directories in Doxyfile via CMake variables
set(DOXYGEN_HTML_DIR ${DOXYGEN_OUT}/html)

add_custom_command(
        TARGET Core
        COMMAND doxygen ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
)

# Ensure the output directory exists
file(MAKE_DIRECTORY ${DOXYGEN_OUT})

target_link_libraries(Core glfw)