cmake_minimum_required(VERSION 3.29)
project(SaturnFramework)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR "source")
set(INCLUDE_DIR "include")
set(VENDOR_DIR "Vendor")
set(GLFW_LIBRARY_TYPE "STATIC")
set(GLFW_INSTALL True)

include_directories(
        ${CMAKE_SOURCE_DIR}/${VENDOR_DIR}/glfw/include
        ${CMAKE_SOURCE_DIR}/${VENDOR_DIR}/spdlog/include
        ${CMAKE_SOURCE_DIR}/${VENDOR_DIR}/uuid_v4
)

add_subdirectory(Vendor/glfw)
add_subdirectory(Core)
add_subdirectory(Application)
