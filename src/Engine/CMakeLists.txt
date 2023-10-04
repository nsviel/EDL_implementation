# Source files
file(GLOB_RECURSE ALL_SOURCES
  ./*.cpp
)

# Define the library target
add_library(LIBRARY_ENGINE STATIC
  ${ALL_SOURCES}
)

# Specify include directories
target_include_directories(LIBRARY_ENGINE PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# Link any external libraries that this library depends on
target_link_libraries(LIBRARY_ENGINE PUBLIC

)
