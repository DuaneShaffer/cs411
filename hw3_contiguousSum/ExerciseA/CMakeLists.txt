cmake_minimum_required(VERSION 3.5.1)
project(hw3)

# Compiler Options
set(CMAKE_CXX_FLAGS "-O3 -Wall")
set (CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cpp")

add_executable(file.out ${SOURCES})
