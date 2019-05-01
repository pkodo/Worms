cmake_minimum_required(VERSION 3.13)
project(SEP19_Group21486)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(.)

add_executable(SEP19_Group21486
        Field.cpp
        Field.h
        Game.cpp
        Game.h
        Random.cpp
        Random.h
        main.cpp Command.cpp Command.h Worm.cpp Worm.h Weapon.cpp Weapon.h Move.cpp Move.h Chest.cpp Chest.h State.cpp State.h Map.cpp Map.h Action.cpp Action.h Choose.cpp Choose.h Help.cpp Help.h Gun.cpp Gun.h Bazooka.cpp Bazooka.h Teleport.cpp Teleport.h Blowtorch.cpp Blowtorch.h Melee.cpp Melee.h Airstrike.cpp Airstrike.h Quit.cpp Quit.h)
