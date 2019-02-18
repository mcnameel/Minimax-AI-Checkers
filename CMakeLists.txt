# cmake_minimum_required(VERSION <specify CMake version here>)
project(Checkers_01)

set(CMAKE_CXX_STANDARD 14)

add_executable(Checkers_01 main.cpp Checker.cpp Checker.h Board.cpp Board.h Player.h Parser.cpp Parser.h Move.cpp Move.h GameManager.cpp GameManager.h Rules.cpp Rules.h AI.cpp AI.h)