cmake_minimum_required(VERSION 3.10)

project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(chess_engine
    source/source.cpp
    source/board.cpp
    source/fen.cpp
    source/Movegeneration.cpp
    source/Movevalidation.cpp
    source/Display.cpp
    source/Makemove.cpp
    source/Moverparser.cpp
)
