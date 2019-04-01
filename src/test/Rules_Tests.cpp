//
// Created by Luke McNamee on 2019-03-13.
//


#include "../../include/external/Catch2/catch.hpp"
#include "../../include/internal/Checker.h"
#include "../../include/internal/Board.h"
#include "../../include/internal/Rules.h"

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
    expected1->setNextChainMove(m2);
    auto *m3 = new Move(3, 5, 5, 7, 4, 6, RED);
    m2->setNextChainMove(m3);
    auto *m4 = new Move(5, 7, 7, 5, 6, 6, RED);
    m3->setNextChainMove(m4);

    Move *expected2 = new Move(7, 5, 5, 7, 6, 6, RED);
    m2 = new Move(5, 7, 3, 5, 4, 6, RED);
    expected2->setNextChainMove(m2);
    m3 = new Move(3, 5, 5, 3, 4, 4, RED);
    m2->setNextChainMove(m3);
    m4 = new Move(5, 3, 7, 5, 6, 4, RED);
    m3->setNextChainMove(m4);

    std::vector<Move *> *actual = Rules::getAllLegalMoves(board);

    bool found1 = false;
    bool found2 = false;

    Move *actual1 = (*actual)[0];
    Move *actual2 = (*actual)[1];

    if(*expected1 == *actual1 || *expected1 == *actual2) {
        found1 = true;
    }
    if(*expected2 == *actual1 || *expected2 == *actual2) {
        found2 = true;
    }
    REQUIRE((found1 && found2));
}


/**
 * Check that when a piece is captured that it is removed from the vector
 * holding the pieces of a specific color
 @setup:
   -------------------
7 |   |   | r |   | r |
  |-------------------|
6 |   | w |   | w |   |
  |-------------------|
5 |   |   |   |   |   |
  |-------------------|
4 |   | w |   | w |   |
  |-------------------|
3 |   |   |   |   |   |
   -------------------
    d   e   f   g    h
White's turn
 */
TEST_CASE("Rules::getAllLegalMoves | multiple captures available lets either one be taken") {
    auto *r1 = new Checker(RED, 7, 5);
    auto *r2 = new Checker(RED, 7, 7);
    auto *w1 = new Checker(WHITE, 6, 4);
    auto *w2 = new Checker(WHITE, 6, 6);
    auto *w3 = new Checker(WHITE, 4, 4);
    auto *w4 = new Checker(WHITE, 4, 6);
    auto pieces = new std::vector<Checker *>();
    pieces->push_back(r1);
    pieces->push_back(r2);
    pieces->push_back(w1);
    pieces->push_back(w2);
    pieces->push_back(w3);
    pieces->push_back(w4);
    auto *board = new Board(pieces, RED);

    auto *expected1 = new Move(7, 5, 5, 3, 6, 4, RED);
    auto *m2 = new Move(5, 3, 3, 5, 4, 4, RED);
    expected1->setNextChainMove(m2);

    auto *expected2 = new Move(7, 5, 5, 7, 6, 6, RED);
    m2 = new Move(5, 7, 3, 5, 4, 6, RED);
    expected2->setNextChainMove(m2);

    auto *expected3 = new Move(7, 7, 5, 5, 6, 4, RED);
    m2 = new Move(5, 5, 3, 7, 4, 6, RED);
    expected3->setNextChainMove(m2);

    auto *expected4 = new Move(7, 7, 5, 5, 6, 4, RED);
    m2 = new Move(5, 5, 3, 3, 4, 4, RED);
    expected4->setNextChainMove(m2);

    bool l1 = Rules::legalMoveFromColor(expected1, board);
    bool l2 = Rules::legalMoveFromColor(expected2, board);
    bool l3 = Rules::legalMoveFromColor(expected3, board);
    bool l4 = Rules::legalMoveFromColor(expected4, board);
    bool success = l1 && l2 && l3 && l4;
    REQUIRE(success);
}


/**
 * Check that when a piece is captured that it is removed from the vector
 * holding the pieces of a specific color
 @setup:
   -------------------
7 |   |   |   |   |   |
  |-------------------|
6 |   | r |   |   |   |
  |-------------------|
5 |   |   |   |   |   |
  |-------------------|
4 |   | r |   | r |   |
  |-------------------|
3 | w |   | w |   |   |
   -------------------
    d   e   f   g    h
White's turn
 */
TEST_CASE("Rules::getAllLegalMoves | multiple captures available lets either one be taken if one becomes a king") {
    auto *w1 = new Checker(WHITE, 3, 3);
    auto *w2 = new Checker(WHITE, 3, 5);
    auto *r1 = new Checker(RED, 6, 4);
    auto *r2 = new Checker(RED, 4, 4);
    auto *r3 = new Checker(RED, 4, 6);
    auto pieces = new std::vector<Checker *>();
    pieces->push_back(r1);
    pieces->push_back(w1);
    pieces->push_back(w2);
    pieces->push_back(r3);
    pieces->push_back(r2);
    auto *board = new Board(pieces, WHITE);

    auto *expected1 = new Move(3, 3, 5, 5, 4, 4, WHITE);
    auto *m2 = new Move(5, 5, 7, 3, 6, 4, WHITE);
    m2->setKingMove(true);
    expected1->setNextChainMove(m2);

    auto *expected2 = new Move(3, 5, 5, 3, 4, 4, WHITE);
    m2 = new Move(5, 3, 7, 5, 6, 4, WHITE);
    m2->setKingMove(true);
    expected2->setNextChainMove(m2);

    auto *expected3 = new Move(3, 5, 5, 7, 4, 6, WHITE);

    bool l1 = Rules::legalMoveFromColor(expected1, board);
    bool l2 = Rules::legalMoveFromColor(expected2, board);
    bool l3 = Rules::legalMoveFromColor(expected3, board);
    bool success = l1 && l2 && l3;
    REQUIRE(success);
}
