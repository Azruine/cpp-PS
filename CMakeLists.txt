cmake_minimum_required(VERSION 3.16.3)
project(mixed_project VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE C_SOURCES "*.c")
file(GLOB_RECURSE CXX_SOURCES "*.cpp")

if(C_SOURCES)

endif()

if(CXX_SOURCES)
    add_executable(temp src/temp.cpp)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

option(C_FLAG_PROFILE "")
if (${C_FLAG_PROFILE})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
endif()

option(CXX_FLAG_PROFILE "")
if (${CXX_FLAG_PROFILE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif()
