cmake_minimum_required(VERSION 3.29)
project(Application)
set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_SOURCE_DIR}/Core/include
        source/
)
file(GLOB_RECURSE APP_INCLUDE_LIST
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE APP_SOURCE_LIST
        "${SOURCE_DIR}/*.cpp"
)

add_executable(Application
        ${APP_INCLUDE_LIST}
        ${APP_SOURCE_LIST}
)

target_precompile_headers(Application PRIVATE "${SOURCE_DIR}/pch.hpp")
target_link_libraries(Application Core)
set_target_properties(
        Application
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}
)

add_custom_command(
        TARGET Application
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}/assets
        COMMENT "Assets copied to output folder."
)