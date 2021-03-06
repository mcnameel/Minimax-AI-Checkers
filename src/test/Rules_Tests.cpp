//
// Created by Luke McNamee on 2019-03-13.
//


#include "../../include/external/Catch2/single_include/catch2/catch.hpp"
#include "../../include/internal/Checker.h"
#include "../../include/internal/Board.h"
#include "../../include/internal/Rules.h"

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
TEST_CASE("Rules::getAllLegalMoves | red multicapture landing in starting space") {
    auto *c1 = new Checker(RED, 7, 5);
    c1->makeKing();
    auto *c2 = new Checker(WHITE, 6, 4);
    auto *c3 = new Checker(WHITE, 6, 6);
    auto *c4 = new Checker(WHITE, 4, 4);
    auto *c5 = new Checker(WHITE, 4, 6);
    auto pieces = new std::vector<Checker *>();
    pieces->emplace_back(c1);
    pieces->emplace_back(c2);
    pieces->emplace_back(c3);
    pieces->emplace_back(c4);
    pieces->emplace_back(c5);
    auto *board = new Board(pieces, RED, nullptr, false);

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
7 |   |   | W |   |   |
  |-------------------|
6 |   | r |   | r |   |
  |-------------------|
7 |   |   |   |   |   |
  |-------------------|
6 |   | r |   | r |   |
  |-------------------|
5 |   |   |   |   |   |
   -------------------
    d   e   f   g    h
White's turn
 */
TEST_CASE("Rules::getAllLegalMoves | white multicapture landing in starting space") {
    auto *w1 = new Checker(WHITE, 7, 5);
    w1->makeKing();
    auto *r1 = new Checker(RED, 6, 4);
    auto *r2 = new Checker(RED, 6, 6);
    auto *r3 = new Checker(RED, 4, 4);
    auto *r4 = new Checker(RED, 4, 6);
    auto pieces = new std::vector<Checker *>();
    pieces->emplace_back(w1);
    pieces->emplace_back(r1);
    pieces->emplace_back(r2);
    pieces->emplace_back(r3);
    pieces->emplace_back(r4);
    auto *board = new Board(pieces, WHITE, nullptr, false);

    auto *expected1 = new Move(7, 5, 5, 3, 6, 4, WHITE);
    auto *m2 = new Move(5, 3, 3, 5, 4, 4, WHITE);
    expected1->setNextChainMove(m2);
    auto *m3 = new Move(3, 5, 5, 7, 4, 6, WHITE);
    m2->setNextChainMove(m3);
    auto *m4 = new Move(5, 7, 7, 5, 6, 6, WHITE);
    m3->setNextChainMove(m4);

    Move *expected2 = new Move(7, 5, 5, 7, 6, 6, WHITE);
    m2 = new Move(5, 7, 3, 5, 4, 6, WHITE);
    expected2->setNextChainMove(m2);
    m3 = new Move(3, 5, 5, 3, 4, 4, WHITE);
    m2->setNextChainMove(m3);
    m4 = new Move(5, 3, 7, 5, 6, 4, WHITE);
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
7 |   |   |   |   |   |
  |-------------------|
6 |   | r |   | r |   |
  |-------------------|
7 |   |   |   |   | w |
  |-------------------|
6 |   | r |   | r |   |
  |-------------------|
5 |   |   |   |   |   |
   -------------------
    d   e   f   g    h
White's turn
 */
TEST_CASE("Rules::getAllLegalMoves | white multicapture ending in kingmove") {
    /* set up */
    auto *w1 = new Checker(WHITE, 5, 7);
    auto *r1 = new Checker(RED, 6, 4);
    auto *r2 = new Checker(RED, 6, 6);
    auto *r3 = new Checker(RED, 4, 4);
    auto *r4 = new Checker(RED, 4, 6);
    auto pieces = new std::vector<Checker *>({r1, r2, r3, r4, w1});

    pieces->emplace_back(w1);
    pieces->emplace_back(r1);
    pieces->emplace_back(r2);
    pieces->emplace_back(r3);
    pieces->emplace_back(r4);
    auto *board = new Board(pieces, WHITE, nullptr, false);

    /* condition */
    auto *expected = new Move(5, 7, 7, 5, 6, 6, WHITE);
    expected->setKingMove(true);

    Move *actual = (*Rules::getAllLegalMoves(board))[0];

    bool found = false;

    if(*expected == *actual) {
        found = true;
    }

    REQUIRE(found);
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
    auto pieces = new std::vector<Checker *>({r1, r2, w3, w4, w1, w2});

    auto *board = new Board(pieces, RED, nullptr, false);

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
auto pieces = new std::vector<Checker *>({r1, r2, r3, w1, w2});
auto *board = new Board(pieces, WHITE, nullptr, false);

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

TEST_CASE("Rules::getAllLegalMoves | edge case") {
    auto *r1 = new Checker(WHITE, 1, 1);
    auto pieces = new std::vector<Checker *>({r1});
    auto *board = new Board(pieces, WHITE, nullptr, false);

    auto *expected1 = new Move(1, 1, 2, 0, -1, -1, WHITE);

    bool l1 = Rules::legalMoveFromColor(expected1, board);
    bool success = l1;
    REQUIRE(success);
}

/**
 * e6 to move
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   | W |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   |   |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   | R |   | r |
  |-------------------------------|
2 | r |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   |   |   |   |   | R |   |   |
  |-------------------------------|
0 |   |   | w |   |   |   |   |   |
   -------------------------------   White: 2
    a   b   c   d   e   f   g   h    Red:   4

 */
TEST_CASE("Ruels | Test case: Edge case") {
    auto *w1 = new Checker(WHITE, 0, 2);
    auto *w2 = new Checker(WHITE, 6, 4);
    w2->makeKing();
    auto *r1 = new Checker(RED, 3, 5);
    r1->makeKing();
    auto *r2 = new Checker(RED, 3, 7);
    auto *r3 = new Checker(RED, 1, 5);
    r3->makeKing();
    auto *r4 = new Checker(RED, 2, 0);

    auto *pieces = new std::vector<Checker*>({w1, w2, r1, r2, r3, r4});
    auto *board = new Board(pieces, WHITE, nullptr, false);

    auto *expected1 = new Move(6, 4, 7, 5, -1, -1, WHITE);
    bool l1 = Rules::legalMoveFromColor(expected1, board);
    REQUIRE(l1);
}

/*
 *   |-------------------------------|
7 |   |   |   | W |   |   |   |   |
  |-------------------------------|
6 | r |   | r |   |   |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   |   |   | r |
  |-------------------------------|
4 | r |   |   |   | r |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|
2 | w |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   | R |   |   |   |   |   | w |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White:
 */