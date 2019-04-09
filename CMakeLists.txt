cmake_minimum_required(VERSION 3.13)
project(Minimax_AI_Checkers_02)

set(CMAKE_CXX_STANDARD 14)

add_executable(Minimax_AI_Checkers src/main/main.cpp src/main/POCO/Checker.cpp include/internal/Checker.h src/main/Board.cpp include/internal/Board.h include/internal/Player.h src/main/human/Parser.cpp include/internal/Parser.h src/main/POCO/Move.cpp include/internal/Move.h src/main/GameManager.cpp include/internal/GameManager.h src/main/Rules.cpp include/internal/Rules.h src/main/AI/AI_Minimax_01.cpp include/internal/AI_Minimax_01.h include/internal/Color.h src/main/AI/Node.cpp include/internal/Node.h include/internal/AI.h src/main/AI/AI_Minimax_02.cpp include/internal/AI_Minimax_02.h src/main/AI/AI.cpp src/main/AI/AI_Minimax_03.cpp include/internal/AI_Minimax_03.h include/internal/AI_Minimax_04.h src/main/AI/AI_Minimax_04.cpp)
add_executable(Minimax_AI_Checkers_Test include/external/Catch2/catch.hpp src/test/Main_Tests.cpp src/main/POCO/Checker.cpp include/internal/Checker.h src/main/Board.cpp include/internal/Board.h include/internal/Player.h src/main/human/Parser.cpp include/internal/Parser.h src/main/POCO/Move.cpp include/internal/Move.h src/main/GameManager.cpp include/internal/GameManager.h src/main/Rules.cpp include/internal/Rules.h src/main/AI/AI_Minimax_01.cpp include/internal/AI_Minimax_01.h include/internal/Color.h src/main/AI/Node.cpp include/internal/Node.h include/internal/AI.h src/main/AI/AI_Minimax_02.cpp include/internal/AI_Minimax_02.h src/main/AI/AI.cpp src/main/AI/AI_Minimax_03.cpp include/internal/AI_Minimax_03.h src/test/Main_Tests.cpp src/test/Board_Tests.cpp src/test/AI_Tests.cpp src/test/Rules_Tests.cpp src/test/Node_Tests.cpp)
#add_executable(Minimax_AI_Checkers_Test Catch2/catch.hpp src/main/POCO/Checker.cpp src/main/POCO/Checker.h src/main/Board.cpp src/main/Board.h src/main/misc/Player.h src/main/human/Parser.cpp src/main/human/Parser.h src/main/POCO/Move.cpp src/main/POCO/Move.h src/main/GameManager.cpp src/main/GameManager.h src/main/Rules.cpp src/main/Rules.h src/main/AI/AI_Minimax_01.cpp src/main/AI/AI_Minimax_01.h src/main/misc/Color.h src/main/AI/Node.cpp src/main/AI/Node.h src/main/AI/MinimaxTree.cpp src/main/AI/MinimaxTree.h src/test/tests-main.cpp src/test/Board_Tests.cpp src/test/Board_Tests.h src/test/AI_Tests.cpp src/test/Rules_Tests.cpp)

#target_link_libraries(Checkers_01_Test Catch2)
# As usual with CMake, add_test takes care of introducing the tests to CTest:

#enable_testing()
#add_test(NAME MyAwesomeTest COMMAND Checkers_01_Test)

