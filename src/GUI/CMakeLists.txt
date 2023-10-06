find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Source files
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
)

# Define the library target
add_library(LIBRARY_GUI STATIC
  ${ALL_SOURCES}
)

# Specify include directories
target_include_directories(LIBRARY_GUI PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# Link any external libraries that this library depends on
target_link_libraries(LIBRARY_GUI PUBLIC
  Eigen3::Eigen #Eigen library
  LIBRARY_EXTERN
  LIBRARY_STATIC
  LIBRARY_ENGINE
)
