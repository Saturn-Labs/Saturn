cmake_minimum_required(VERSION 3.29)
project(SaturnFrameworkCore)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
        ${INCLUDE_DIR}
        ${SOURCE_DIR}
)

file(GLOB_RECURSE API_INCLUDE_LIST
        "${INCLUDE_DIR}/*.h"
        "${INCLUDE_DIR}/*.hpp"
        "${CMAKE_SOURCE_DIR}/${VENDOR_DIR}/glad/src/gl.c"
)

file(GLOB_RECURSE INCLUDE_LIST
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE SOURCE_LIST
        "${SOURCE_DIR}/*.cpp"
)

add_library(SaturnFrameworkCore STATIC
    ${API_INCLUDE_LIST}
    ${INCLUDE_LIST}
    ${SOURCE_LIST}
)

target_link_libraries(SaturnFrameworkCore glfw)