# Project
cmake_minimum_required(VERSION 3.5)
project(NEPHOS LANGUAGES CXX)

# CMake variables
set(WINDOWS_COMPILATION 0)

# General policy
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WINDOWS_COMPILATION)
  set(CMAKE_SYSTEM_NAME Windows)
  set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc-posix)
  set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++-posix)
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_AR x86_64-w64-mingw32-ar)
  set(CMAKE_RANLIB x86_64-w64-mingw32-ranlib)

  # Add cross-compiled GLFW library and header files
  include_directories(bin/lib/glfw)
  link_directories(bin/lib/glfw)

  # Add cross-compiled Vulkan SDK library and header files
  include_directories(bin/lib/vulkansdk)
  link_directories(bin/lib/vulkansdk)
  include_directories(bin/lib/vulkansdk/vulkan)
  find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS bin/lib/vulkansdk/lib)
  link_libraries(${Vulkan_LIBRARY})

  # Add cross-compiled GLM
  include_directories(bin/lib/glm)
  link_directories(bin/lib/glm)

endif()



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

# Denpendancies
set(ALL_LIBS
  ${GLFW_LIBRARY}
  ${Vulkan_LIBRARIES}

  #Vulkan::Vulkan
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
  SQLiteCpp
  pthread
  dl
)

# Executable
add_executable(executable
  ${ALL_SOURCES}
)

# Library linking
target_link_libraries(executable
  LIBRARY_EXTERN
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
