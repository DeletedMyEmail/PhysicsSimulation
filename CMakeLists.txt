cmake_minimum_required(VERSION 3.28)
project(SimulationGoesBRr)
cmake_policy(SET CMP0072 NEW)

FIND_PACKAGE(OpenGL REQUIRED)
set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE SOURCE "src/*.cpp" "src/*.c" "include/*.h" "include/*.hpp" "libs/*.cpp" "libs/*.c" "libs/*.h" "libs/*.hpp")
add_executable(SimulationGoesBRr ${SOURCE}
        src/Input.cpp
        include/Input.h)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)