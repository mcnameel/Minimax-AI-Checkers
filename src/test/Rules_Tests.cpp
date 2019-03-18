//
// Created by Luke McNamee on 2019-03-13.
//


#include "../../Catch2/catch.hpp"
#include "../main/POCO/Checker.h"
#include "../main/Board.h"
#include "../main/Rules.h"

/**
 * Check that when a piece is captured that it is removed from the vector
 * holding the pieces of a specific color
 @setup:
   -------------------
7 |   |   | r |   |   |
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
White's turn
 */
TEST_CASE("Rules::getAllLegalMoves | multicapture landing in starting space") {
    auto *c1 = new Checker(RED, 7, 5);
    c1->makeKing();
    auto *c2 = new Checker(WHITE, 6, 4);
    auto *c3 = new Checker(WHITE, 6, 6);
    auto *c4 = new Checker(WHITE, 4, 4);
    auto *c5 = new Checker(WHITE, 4, 6);
    auto pieces = new std::vector<Checker *>();
    pieces->push_back(c1);
    pieces->push_back(c2);
    pieces->push_back(c3);
    pieces->push_back(c4);
    pieces->push_back(c5);
    auto *board = new Board(pieces, RED);


    auto *expected1 = new Move(7, 5, 5, 3, 6, 4, RED);
    auto *m2 = new Move(5, 3, 3, 5, 4, 4, RED);
    expected1->setChainMove(m2);
    auto *m3 = new Move(3, 5, 5, 7, 4, 6, RED);
    m2->setChainMove(m3);
    auto *m4 = new Move(5, 7, 7, 5, 6, 6, RED);
    m3->setChainMove(m4);
    //m4->setKingMove(true);

    Move *expected2 = new Move(7, 5, 5, 7, 6, 6, RED);
    m2 = new Move(5, 7, 3, 5, 4, 6, RED);
    expected2->setChainMove(m2);
    m3 = new Move(3, 5, 5, 3, 4, 4, RED);
    m2->setChainMove(m3);
    m4 = new Move(5, 3, 7, 5, 6, 4, RED);
    m3->setChainMove(m4);
   // m4->setKingMove(true);

    std::vector<Move *> *actual = Rules::getAllLegalMoves(board);

    bool found1 = false;
    bool found2 = false;

    Move *actual1 = actual->at(0);
    Move *actual2 = actual->at(1);

    if(*expected1 == *actual1 || *expected1 == *actual2) {
        found1 = true;
    }
    if(*expected2 == *actual1 || *expected2 == *actual2) {
        found2 = true;
    }
    REQUIRE((found1 && found2));
}
