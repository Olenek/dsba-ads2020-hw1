cmake_minimum_required(VERSION 3.14)
project(contest_solutions)

set(CMAKE_CXX_STANDARD 17)

add_executable(multiplication-workshop main.cpp src/Multiplicator.cpp src/Number.cpp src/Experimentator.cpp)
add_executable(multiplication-workshop_2 main.cpp src/Multiplicator.cpp src/Number.cpp src/Experimentator.cpp)

#add_executable(multiplication-workshop_OLD main.cpp src/Multiplicator.cpp src/Number.cpp)
#For the old version (MAY NOT WORK)