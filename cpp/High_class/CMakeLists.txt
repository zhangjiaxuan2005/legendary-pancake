cmake_minimum_required(VERSION 3.31)
project(High_class)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-fno-elide-constructors)

add_executable(Vector STL/Vector.cpp)
add_executable(List STL/List.cpp)
add_executable(Set STL/Set.cpp)
add_executable(Map STL/Map.cpp)

add_executable(namespace AdvanceFeature/namespace.cpp)
add_executable(MoveSemantics AdvanceFeature/MoveSemantics.cpp)
add_executable(RAII AdvanceFeature/RAII.cpp)
add_executable(Lambda AdvanceFeature/Lambda.cpp)
