cmake_minimum_required(VERSION 3.13)
project(Minimax_AI_Checkers_02)

set(CMAKE_CXX_STANDARD 14)

add_executable(Minimax_AI_Checkers src/main/main.cpp src/main/POCO/Checker.cpp include/internal/Checker.h src/main/Board.cpp include/internal/Board.h include/internal/Player.h src/main/human/Parser.cpp include/internal/Parser.h src/main/POCO/Move.cpp include/internal/Move.h src/main/GameManager.cpp include/internal/GameManager.h src/main/Rules.cpp include/internal/Rules.h src/main/AI/AI_Minimax_01.cpp include/internal/AI_Minimax_01.h include/internal/Color.h src/main/AI/Node.cpp include/internal/Node.h include/internal/AI.h src/main/AI/AI_Minimax_02.cpp include/internal/AI_Minimax_02.h src/main/AI/AI.cpp src/main/AI/AI_Minimax_03.cpp include/internal/AI_Minimax_03.h src/main/AI/AI_Minimax_04.cpp include/internal/AI_Minimax_04.h)
add_executable(Minimax_AI_Checkers_Test include/external/Catch2/catch.hpp src/test/Main_Tests.cpp src/main/POCO/Checker.cpp include/internal/Checker.h src/main/Board.cpp include/internal/Board.h include/internal/Player.h src/main/human/Parser.cpp include/internal/Parser.h src/main/POCO/Move.cpp include/internal/Move.h src/main/GameManager.cpp include/internal/GameManager.h src/main/Rules.cpp include/internal/Rules.h src/main/AI/AI_Minimax_01.cpp include/internal/AI_Minimax_01.h include/internal/Color.h src/main/AI/Node.cpp include/internal/Node.h include/internal/AI.h src/main/AI/AI_Minimax_02.cpp include/internal/AI_Minimax_02.h src/main/AI/AI.cpp src/main/AI/AI_Minimax_03.cpp include/internal/AI_Minimax_03.h src/test/Main_Tests.cpp src/test/Board_Tests.cpp src/test/Board_Tests.h src/test/AI_Tests.cpp src/test/Rules_Tests.cpp src/test/Node_Tests.cpp)


