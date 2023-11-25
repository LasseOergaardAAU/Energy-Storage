cmake_minimum_required(VERSION 3.1)

project(Energy-Storage C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src)
add_subdirectory(application)
enable_testing()
add_subdirectory(test)
