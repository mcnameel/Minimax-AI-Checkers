# cmake_minimum_required(VERSION <specify CMake version here>)
project(Checkers_01)

set(CMAKE_CXX_STANDARD 14)

add_executable(Checkers_01 src/main/main.cpp src/main/POCO/Checker.cpp src/main/POCO/Checker.h src/main/Board.cpp src/main/Board.h src/main/misc/Player.h src/main/human/Parser.cpp src/main/human/Parser.h src/main/POCO/Move.cpp src/main/POCO/Move.h src/main/GameManager.cpp src/main/GameManager.h src/main/Rules.cpp src/main/Rules.h src/main/AI/AI.cpp src/main/AI/AI.h src/main/misc/Color.h src/main/AI/Node.cpp src/main/AI/Node.h src/main/AI/MinimaxTree.cpp src/main/AI/MinimaxTree.h)