cmake_minimum_required(VERSION 3.16.3)
project(mixed_project VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_CXX_REFLECTION "Enable experimental C++26 reflection" ON)

if(ENABLE_CXX_REFLECTION)
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
       OR CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
        message(FATAL_ERROR "C++ reflection requires GCC 16 or newer")
    endif()

    add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:-freflection>
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Applying release build options")
    add_compile_options(-O3 -Wall)
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
    add_compile_definitions(DEBUG)
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
    add_executable(tempc src/temp.c)
endif()

if(CXX_SOURCES)
    add_executable(temp src/temp.cpp)
    add_executable(testcasegen src/testcasegen.cpp)
    # Keep third-party warnings separate from the project's strict diagnostics.
    target_include_directories(testcasegen SYSTEM PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/testlib"
    )
    add_executable(temp_leetcode src/temp_leetcode.cpp)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
