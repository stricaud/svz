cmake_minimum_required(VERSION 2.8)

project(libsvz)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
message(FATAL_ERROR "CMake generation is not allowed within the source directory!
Remove the CMakeCache.txt file and try again from another folder, e.g.:

   rm CMakeCache.txt
   mkdir build
   cd build
   cmake ..
")
endif()

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

if (DEBUG_MODE)
add_definitions(-DFAUP_DEBUG=1)
set(CMAKE_BUILD_TYPE "Debug")
        if(NOT WIN32)
                add_definitions(-g)
        endif()
else()
        if(NOT WIN32)
                add_definitions(-O3)
        endif()
endif()
if (NOT WIN32)
	add_definitions(-std=c99 -fPIC)
endif()

include(CTest)

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckLibraryExists)

include(GNUInstallDirs)

find_package(GIF REQUIRED)

set(LIBSVZ_INCLUDE_DIRS "${GIF_INCLUDE_DIRS}" "${libsvz_SOURCE_DIR}/src/include/" "${libsvz_BINARY_DIR}/src/include")
set(LIBSVZ_LINK_LIBRARIES "${GIF_LIBRARIES}" "m")
set(LIBSVZ_LIBRARY "svz")

add_subdirectory(src)
add_subdirectory(tests)

