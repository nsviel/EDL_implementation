# Project
cmake_minimum_required(VERSION 3.5)
project(NEPHOS LANGUAGES CXX)

# General policy
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMakeLists childs
add_subdirectory(extern)
add_subdirectory(src)
