cmake_minimum_required(VERSION 3.13)
project(SEP19_Group21486)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SEP19_Group21486
        Field.cpp
        Field.h
        Game.cpp
        Game.h
        Random.cpp
        Random.h
        main.cpp Command.cpp Command.h Worm.cpp Worm.h Weapon.cpp Weapon.h)
