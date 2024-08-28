cmake_minimum_required(VERSION 3.29)
project(SaturnFrameworkApp)
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

include(CMakePrintHelpers)
message(${APP_SOURCE_LIST})

add_executable(SaturnFrameworkApp
        ${APP_INCLUDE_LIST}
        ${APP_SOURCE_LIST}
)
add_dependencies(SaturnFrameworkApp SaturnFrameworkCore)
target_link_libraries(SaturnFrameworkApp glfw)

target_link_libraries(SaturnFrameworkApp ${CMAKE_SOURCE_DIR}/Output/Core/${CMAKE_BUILD_TYPE}/SaturnFrameworkCore.lib)
set_target_properties(
        SaturnFrameworkApp
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Application/${CMAKE_BUILD_TYPE}
)