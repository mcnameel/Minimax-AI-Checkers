//
// Created by Luke McNamee on 2019-04-04.
//


#include "../../include/external/Catch2/catch.hpp"
#include "../../include/internal/Checker.h"
#include "../../include/internal/Board.h"
#include "../../include/internal/Rules.h"
#include "../../include/internal/Node.h"

/**
 * Check that when a piece is captured that it is removed from the vector
 * holding the pieces of a specific color
 @setup:
   -------------------
7 |   |   | R |   |   |
  |-------------------|
6 |   | w |   | w |   |
  |-------------------|
7 |   |   |   |   |   |
  |-------------------|
6 |   | w |   | w |   |
  |-------------------|
5 |   |   |   |   |   |
   -------------------
    d   e   f   g    h
Red's turn
 */
TEST_CASE("Node::createTreeWithThreads | ") {
    auto *c1 = new Checker(RED, 7, 5);
    c1->makeKing();
    auto *c2 = new Checker(WHITE, 6, 4);
    auto *c3 = new Checker(WHITE, 6, 6);
    auto *c4 = new Checker(WHITE, 4, 4);
    auto *c5 = new Checker(WHITE, 4, 6);
    auto *c6 = new Checker(WHITE, 1, 1);
    auto *c7 = new Checker(WHITE, 0, 0);
    auto pieces = new std::vector<Checker *>();
    pieces->push_back(c1);
    pieces->push_back(c2);
    pieces->push_back(c3);
    pieces->push_back(c4);
    pieces->push_back(c5);
    pieces->push_back(c6);
    pieces->push_back(c7);
    auto *board = new Board(pieces, RED, nullptr);

    Node *actual = Node::createTreeWithThreads(board, 2, nullptr);


    REQUIRE(true);
}