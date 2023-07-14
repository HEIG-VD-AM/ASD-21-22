cmake_minimum_required(VERSION 3.16)
project(ASD2022-L2-Recursivite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")
add_executable(L2-recursivite main.cpp pieces.cpp check.cpp solve.cpp piece_manip.cpp)