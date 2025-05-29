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
add_compile_options("-Wno-braced-scalar-init") # Learncpp 13.8: overcome Clang bug

# # Run with address sanitizer
# add_compile_options("-fsanitize=address")
# add_link_options("-fsanitize=address")

if(MINGW)
    message(STATUS "Building with mingw-w64")
else()
    message(STATUS "Not building with mingw-w64")
endif()

message(STATUS "SUBLIME_CURRENT_FILE is set to: ${SUBLIME_CURRENT_FILE}")
add_executable(Test ${SUBLIME_CURRENT_FILE} CInTools.cpp)