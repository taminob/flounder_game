cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(flounder_game)

# if not specified otherwise, build in release mode
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# enable generation of compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

set(OPTIMIZE_FLAGS "-O2")
set(DEBUG_FLAGS "-g3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS YES)

set(CMAKE_CXX_FLAGS
    "-fsanitize=undefined -pthread -ffast-math -Wall -Wextra -Wno-psabi -pedantic-errors"
)
set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${DEBUG_FLAGS} ${OPTIMIZE_FLAGS}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

message(STATUS "Compiling in ${CMAKE_BUILD_TYPE} mode")
