cmake_minimum_required(VERSION 3.14)
project(contest_solutions)

set(CMAKE_CXX_STANDARD 17)
add_executable(multiplication-workshop main.cpp src/Multiplicator.cpp src/Number.cpp)
#add_executable(contest_solutions contest.cpp )