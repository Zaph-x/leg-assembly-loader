cmake_minimum_required(VERSION 3.15)
project(arm CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

include(dependencies/doctest.cmake)
include_directories(include)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
