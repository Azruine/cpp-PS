cmake_minimum_required(VERSION 3.16.3)
project(mixed_project VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Applying release build options")
    add_compile_options(-O2 -Wall)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Applying debug build options")
    add_compile_options(
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -Wpedantic
        -Wshadow
        -Wunused
    )
endif()

option(C_FLAG_PROFILE "Enable profiling for C" OFF)
option(CXX_FLAG_PROFILE "Enable profiling for C++" OFF)

if(C_FLAG_PROFILE)
    message(STATUS "Profiling enabled for C")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
endif()

if(CXX_FLAG_PROFILE)
    message(STATUS "Profiling enabled for C++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

file(GLOB_RECURSE C_SOURCES "*.c")
file(GLOB_RECURSE CXX_SOURCES "*.cpp")

if(C_SOURCES)

endif()

if(CXX_SOURCES)
    add_executable(temp src/temp.cpp)
    add_executable(testcasegen src/testcasegen.cpp)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
