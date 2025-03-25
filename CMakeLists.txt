cmake_minimum_required(VERSION 3.26)
project(Project1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE "Release")
#add_subdirectory(lib/googletest)
#include_directories(lib/googletest/googletest/include)
#include_directories(lib/googletest/googlemock/include)
include_directories(Code)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP})

add_executable(Project
        data_structures/MutablePriorityQueue.h
        Code/Main.cpp
        Code/Dijkstra.cpp
        Code/Menu.cpp
        Code/Driving_only.h
        Code/Batch_Mode_read.h
)

#add_executable(Main
        #Code/Main.cpp
        #Code/Menu.cpp)

#add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
#set(CMAKE_CXX_FLAGS_DEBUG "/MDd")  # Para Debug
#set(CMAKE_CXX_FLAGS_RELEASE "/MD") # Para Release
#target_link_libraries(da2425_p03_student gtest gtest_main gmock gmock_main)
