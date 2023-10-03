# Source files
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
  *.hpp
  *.h
)

# Define the library target
add_library(LIBRARY_EXTERN
  ${ALL_SOURCES}
)

# Specify include directories
target_include_directories(LIBRARY_EXTERN PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# Link any external libraries that this library depends on
target_link_libraries(LIBRARY_EXTERN PUBLIC
  ${CMAKE_DL_LIBS}
)
