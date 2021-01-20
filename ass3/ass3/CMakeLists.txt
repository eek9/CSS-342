cmake_minimum_required(VERSION 3.10)
project(maze)

set(CMAKE_CXX_STANDARD 14)

# need to load data files from current directory as cpp files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(.)

add_executable(maze
              main.cpp
              maze.cpp
              maze.h
              creature.cpp
              creature.h)