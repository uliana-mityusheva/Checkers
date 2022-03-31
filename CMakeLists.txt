cmake_minimum_required(VERSION 3.17)
project(Checkers)

set(CMAKE_CXX_STANDARD 20)

add_executable(Checkers main.cpp Board.h Board.cpp Reader.cpp Reader.h Printer.cpp Printer.h Transformer.cpp Transformer.h Coordinates.h Coordinates.cpp Game.cpp Game.h StringConst.h)