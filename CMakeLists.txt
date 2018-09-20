cmake_minimum_required(VERSION 3.5.1)
project(assn01)
set (CMAKE_CXX_STANDARD 11)
include_directories(headers)

file(GLOB SOURCES "*.cpp")

add_executable(file.out ${SOURCES})
