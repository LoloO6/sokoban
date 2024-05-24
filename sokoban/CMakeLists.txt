cmake_minimum_required(VERSION 3.27)
project(sokoban)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib CONFIG REQUIRED)
add_executable(sokoban sokoban.cpp globals.h
        levels.h player.h graphics.h
        images.h sounds.h player.cpp parser.h
        levels.cpp level_manager.h)
target_link_libraries(sokoban PRIVATE raylib)
