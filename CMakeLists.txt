cmake_minimum_required(VERSION 3.29)
project(EatingSnake)

set(CMAKE_CXX_STANDARD 20)

add_executable(EatingSnake main.cpp
        Funcs/Control.cpp
        Funcs/Control.h
        Funcs/Graphic.cpp
        Funcs/Game.cpp
        Funcs/Game.h
        Funcs/Graphic.h
)
