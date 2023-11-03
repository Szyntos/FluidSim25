cmake_minimum_required(VERSION 3.26)
project(FluidSim25)

set(CMAKE_CXX_STANDARD 17)

add_executable(FluidSim25 main.cpp
        glad.c)
target_link_libraries(FluidSim25 -lglfw3)