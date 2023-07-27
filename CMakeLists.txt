cmake_minimum_required(VERSION 3.20)

project(procstat C CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Weverything)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/)
