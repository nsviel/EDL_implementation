# CMakeLists childs
add_subdirectory(Element)
add_subdirectory(Engine)
add_subdirectory(GUI)

# Library dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

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
)

# Source files
file(GLOB_RECURSE ALL_SOURCES
  Application/*.cpp
  config.h
  main.cpp
)

# Executable
add_executable(executable
  ${ALL_SOURCES}
)

# Library linking
target_link_libraries(executable
  LIBRARY_EXTERN
  LIBRARY_STATIC
  LIBRARY_ENGINE
  LIBRARY_GUI
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
