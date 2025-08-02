cmake_minimum_required(VERSION 3.31)
project(High_class)

set(CMAKE_CXX_STANDARD 23)

add_executable(Vector STL/Vector.cpp)
add_executable(List STL/List.cpp)
add_executable(Set STL/Set.cpp)
add_executable(Map STL/Map.cpp)