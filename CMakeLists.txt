cmake_minimum_required(VERSION 3.20)
project(Cabe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(tomlplusplus)


# Set only one backend

set(USE_BACKEND_BASIC ON)
set(USE_BACKEND_GAPBUFFER OFF)

# Set only one frontend

set(USE_FRONTEND_CONSOLE OFF)
set(USE_FRONTEND_SDL3BUILTIN ON)

add_subdirectory(src)