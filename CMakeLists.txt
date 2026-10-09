cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(snake
    Game.cpp
    Snake.cpp
    Renderer.cpp
    Cell.cpp
    Rand.cpp
)