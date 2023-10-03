# Project
cmake_minimum_required(VERSION 3.5)
project(NEPHOS LANGUAGES CXX)

# General policy
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

# Source files
file(GLOB_RECURSE ALL_SOURCES
  src/*.cpp
)

# Child CMakeLists
add_subdirectory(extern)
add_subdirectory(src/Element)

# Denpendancies
set(ALL_LIBS
  ${GLFW_LIBRARY}
  ${Vulkan_LIBRARIES}

  Eigen3::Eigen #Eigen library
  stdc++fs #STD filesystem experimental
  tins #packet crafting and sniffing library
  -std=c++17 -O2
  -lglfw
  -ldl
  -lpthread
  -lX11
  -lXxf86vm
  -lXrandr
  -lXi
  -lsqlite3
  -lSQLiteCpp #sqlitecpp
  -lpthread #sqlitecpp
  -ldl #sqlitecpp
)

# Executable
add_executable(executable
  ${ALL_SOURCES}
)

# Library linking
target_link_libraries(executable
  LIBRARY_EXTERN
  LIBRARY_ELEMENT
  ${ALL_LIBS}
)

# External source linking
target_sources(executable PRIVATE
  ${EXTERN_TRG_SRC}
)

# Add the binary tree to the search path for include files
target_include_directories(executable PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/extern"
  ${Vulkan_INCLUDE_DIRS}
)
link_libraries(${Vulkan_LIBRARY})
