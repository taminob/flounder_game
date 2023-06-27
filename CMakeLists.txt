cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(flounder_game)

option(ENABLE_TESTS "Enable compilation of tests" OFF)

find_package(Boost 1.68.0 REQUIRED COMPONENTS program_options)
find_package(fmt 8.1.0 REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# if not specified otherwise, build in release mode
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(EXECUTABLE_NAME "flounder_game")
set(LIBRARY_NAME "flounder")

# enable generation of compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

set(OPTIMIZE_FLAGS "-O2")
set(DEBUG_FLAGS "-g3")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS
    "-pthread -ffast-math -Wall -Wextra -Wno-psabi -pedantic-errors -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${DEBUG_FLAGS} ${OPTIMIZE_FLAGS}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

message(STATUS "Compiling in ${CMAKE_BUILD_TYPE} mode")

add_subdirectory(src)

if(${ENABLE_TESTS})
  add_subdirectory(test)
endif()
