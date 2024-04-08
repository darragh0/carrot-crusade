cmake_minimum_required(VERSION 3.27)
project(carrot_crusade)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(carrot_crusade
        src/main.cpp
        src/Map.cpp
        src/Map.h)
