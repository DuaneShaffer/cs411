cmake_minimum_required(VERSION 3.5.1)
project(hw6)

# Compiler Options
set(CMAKE_CXX_FLAGS "-Wall")
set (CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "*.cpp")

add_executable(file.out ${SOURCES})
