project(asciiroguelike)
cmake_minimum_required(VERSION 3.10)

file(GLOB SRC "src/*.cpp")

add_executable(main ${SRC})