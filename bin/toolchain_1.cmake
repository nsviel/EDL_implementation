set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

# cross compilers to use for C, C++ and Fortran
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc-posix)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++-posix)
set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

set(CMAKE_TOOLCHAIN_FILE "build/mingw-w64-x86_64.cmake")

# set the sysroot directory
set(CMAKE_SYSROOT /usr/${TOOLCHAIN_PREFIX})

# set the include directories for the target environment
set(CMAKE_CXX_FLAGS "--sysroot=${CMAKE_SYSROOT} -I${CMAKE_SYSROOT}/include/c++/9.3.0 -I${CMAKE_SYSROOT}/include")
set(CMAKE_EXE_LINKER_FLAGS "--sysroot=${CMAKE_SYSROOT} -L${CMAKE_SYSROOT}/lib")

# set the linker flags
set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# modify default behavior of FIND_XXX() commands
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# add pthreads support for std::thread
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)


