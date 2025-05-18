cmake_minimum_required(VERSION 3.10)
project(Test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_BUILD_TYPE "Debug")

# Colorize build output: https://www.reddit.com/r/cmake/comments/l8ycdq/comment/izgbyfh
set(CMAKE_COLOR_DIAGNOSTICS "ON")
set(CLICOLOR_FORCE 1)

# https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#compilers
add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "-Wold-style-cast" "-Wcast-align" "-Wunused" "-Woverloaded-virtual" "-Wpedantic" "-Wconversion" "-Wsign-conversion" "-Wmisleading-indentation" "-Wnull-dereference" "-Wdouble-promotion" "-Wformat=2" "-Wimplicit-fallthrough" "-Weffc++")

if(MINGW)
    message(STATUS "Building with mingw-w64")
else()
    message(STATUS "Not building with mingw-w64")
endif()

add_executable(Test 8.10.q5.cpp)