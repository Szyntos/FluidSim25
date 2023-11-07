cmake_minimum_required(VERSION 3.26)
project(FluidSim25)

set(CMAKE_CXX_STANDARD 17)

add_executable(FluidSim25 src/main.cpp
        src/glad/glad.c
        src/utils/Shader.cpp
        src/Primitives/Triangle.cpp
        src/Primitives/Point.cpp
        src/Primitives/Quad.cpp
        src/Simulation/Grid.cpp
        src/Simulation/Cell.cpp
        src/utils/Globals.cpp
        src/Primitives/Square.cpp
        src/Primitives/SquareHelper.cpp
        src/Simulation/Sim.cpp
        src/utils/utils.cpp)
target_link_libraries(FluidSim25 -lglfw3)