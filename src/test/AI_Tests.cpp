//
// Created by Luke McNamee on 2019-03-12.
//

#include "../../include/external/Catch2/catch.hpp"
#include "../../include/internal/Checker.h"
#include "../../include/internal/Board.h"
#include "../../include/internal/AI_Evaluation_Impl_01.h"
#include "../../include/internal/AI_Evaluation_Impl_04.h"
#include "../../include/internal/AI_Evaluation_Impl_03.h"
#include "../../include/internal/AI_Evaluation_Impl_02.h"


/**
 * Case: Red's turn and they are capturing a piece
 *
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   | r |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   | w |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|
2 |   |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 1
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

 */
TEST_CASE("Red capture") {
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);

    auto pieces = new std::vector<Checker *>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);

    Board *board = new Board(pieces, RED, nullptr, false);
    //board->printBoard();

    AI_Minimax_01 *player2 = new AI_Minimax_01(2, RED);

    Move *m1 = player2->getMove(board);
    Move *m2 = new Move(6, 4, 4, 6, 5, 5, RED);

    REQUIRE((*m1 == *m2));
}

/**
 * Case: it's White's turn to generate a move and there is only one option for moves
@begin:
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   | r |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   | w |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|
2 |   |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 1
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

@Expected:
 begin:
  |-------------------------------|
7 |   |   |   | w |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   |   |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   |   |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|
2 |   |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 1
    a   b   c   d   e   f   g   h    Red:   0
Red's turn

 */
TEST_CASE("White king-capture") {
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);

    auto pieces = new std::vector<Checker *>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);

    Board *board = new Board(pieces, WHITE, nullptr, false);

    AI_Minimax_01 *player2 = new AI_Minimax_01(2, WHITE);

    Move *m1 = player2->getMove(board);
    Move *m2 = new Move(5, 5, 7, 3, 6, 4, WHITE);
    m2->setKingMove(true);

    REQUIRE((*m1 == *m2));
}


/**
 * Case: it's White's turn to generate a move and there is only one option for moves
@begin:
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   | r |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   |   |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   | r |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   | w |
  |-------------------------------|  White: 1
    a   b   c   d   e   f   g   h    Red:   2
Red's turn

@Expected:
 begin:
  |-------------------------------|
7 |   |   |   | w |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   |   |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   |   |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|  White: 1
    a   b   c   d   e   f   g   h    Red:   0
Red's turn

 */
TEST_CASE("White king-multicapture") {
    /* setup */
    auto pieces = new std::vector<Checker *>();
    auto *r1 = new Checker(RED, 6, 4);
    auto *r2 = new Checker(RED, 4, 6);
    auto *w1 = new Checker(WHITE, 3, 7);
    pieces->emplace_back(r1);
    pieces->emplace_back(r2);
    pieces->emplace_back(w1);

    Move *expected = new Move(3, 7, 5, 5, 4, 6, WHITE);
    Move *expectedChain = new Move(5, 5, 7, 3, 6, 4, WHITE);
    expectedChain->setKingMove(true);
    expected->setNextChainMove(expectedChain);

    /* condition */
    Board *board = new Board(pieces, WHITE, nullptr, false);
    AI_Minimax_01 *player2 = new AI_Minimax_01(2, WHITE);
    Move *actual = player2->getMove(board);

    REQUIRE((*actual == *expected));
}

/**
 * Case: it's WHITE's turn a they will win on this turn
 * check that the Board::isGameOver() == true
 *
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   | r |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   | w |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   | w |
  |-------------------------------|
2 |   |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 2
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

 */
TEST_CASE("Game Over turn after") {
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);
    auto *c3 = new Checker(WHITE, 3, 7);
    auto pieces = new std::vector<Checker *>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);
    pieces->emplace_back(c3);

    auto *board = new Board(pieces, RED, nullptr, false);
    // board->printBoard();

    AI_Minimax_01 *player1 = new AI_Minimax_01(2, RED);

    Move *m = player1->getMove(board);
    board->move(m, true);

    REQUIRE(!board->isGameOver());
}

/**
 * Case: it's WHITE's turn a they will win on this turn
 * check that the Board::isGameOver() == true
 *
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   |   |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   |   |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   | r |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   | w |
  |-------------------------------|
2 |   |   |   |   |   |   |   |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 2
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

 */
TEST_CASE("Game Over this turn") {
    auto *c1 = new Checker(RED, 4, 6);
   // auto *c3 = new Checker(RED, 7, 7);
    auto *c2 = new Checker(WHITE, 3, 7);
    auto pieces = new std::vector<Checker *>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);
    //pieces->emplace_back(c3);

    Board *board = new Board(pieces, WHITE, nullptr, false);
    // board->printBoard();

    AI_Minimax_01 *player2 = new AI_Minimax_01(2, WHITE);

    Move *m = player2->getMove(board);
    board->move(m, true);

    REQUIRE(board->isGameOver());
}

/**
 * Check that when a piece is captured that it is removed from the vector
 * holding the pieces of a specific color
 @setup:
   -------------------
7 |   |   |   |   | r |
  |-------------------|
6 |   | r |   |   |   |
  |-------------------|
5 | w |   | w |   |   |
   -------------------
    d   e   f   g    h
White's turn
 */
TEST_CASE("AI_Minimax_01::getMove() | When black can win in three moves it chooses the correct move") {
    auto *c1 = new Checker(RED, 7, 7);
    auto *c2 = new Checker(RED, 6, 4);
    auto *c3 = new Checker(WHITE, 5, 5);
    auto *c4 = new Checker(WHITE, 5, 3);

    auto pieces = new std::vector<Checker *>();
    pieces->emplace_back(c1);
    pieces->emplace_back(c2);
    pieces->emplace_back(c3);
    pieces->emplace_back(c4);

    auto *board = new Board(pieces, WHITE, nullptr, false);
    auto player2 = new AI_Minimax_02(4, WHITE);
    Move *m1 = player2->getMove(board);
    auto *m2 = new Move(5, 3, 7, 5, 6, 4, WHITE);
    m2->setKingMove(true);
    bool returnMe = (*m1 == *m2);
    REQUIRE(returnMe);
}

/**
 * Case: it's White's turn a they have fewer kings than red. They should move
 * away
 *
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   |   |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   | W |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|
2 |   |   |   |   | R |   | R |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 2
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

 */
TEST_CASE("AI_Minimax_01::getMove() | Check that king flees from other king") {
    auto *r1 = new Checker(RED, 2, 4);
    auto *r2 = new Checker(RED, 2, 6);
    auto *w1 = new Checker(WHITE, 5, 5);
    r1->makeKing();
    r2->makeKing();
    w1->makeKing();

    auto pieces = new std::vector<Checker *>({r1, r2, w1});
    auto *board = new Board(pieces, WHITE, nullptr, true);
    auto *player2 = new AI_Minimax_04(4, WHITE);

    auto *actual = player2->getMove(board);
    auto *expected1 = new Move(5, 5, 6, 6, -1, -1, WHITE);
    auto *expected2 = new Move(5, 5, 6, 4, -1, -1, WHITE);

    bool returnMe = *actual == *expected1 || *actual == *expected2;
    REQUIRE(returnMe);
}


/**
 * Case: it's RED's turn a they have more kings than White. They should move
 * towards
 *
  |-------------------------------|
7 |   |   |   |   |   |   |   |   |
  |-------------------------------|
6 |   |   |   |   |   |   |   |   |
  |-------------------------------|
5 |   |   |   |   |   | W |   |   |
  |-------------------------------|
4 |   |   |   |   |   |   |   |   |
  |-------------------------------|
3 |   |   |   |   |   |   |   |   |
  |-------------------------------|
2 |   |   |   |   | R |   | R |   |
  |-------------------------------|
1 |   |   |   |   |   |   |   |   |
  |-------------------------------|
0 |   |   |   |   |   |   |   |   |
   -------------------------------   White: 2
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

 */
TEST_CASE("AI_Minimax_01::getMove() | Check that king chases the other king") {
auto *r1 = new Checker(RED, 2, 4);
auto *r2 = new Checker(RED, 2, 6);
auto *w1 = new Checker(WHITE, 5, 5);
r1->makeKing();
r2->makeKing();
w1->makeKing();

auto pieces = new std::vector<Checker *>({r1, r2, w1});
auto *board = new Board(pieces, RED, nullptr, true);
auto *player2 = new AI_Minimax_04(2, RED);

auto *expected = player2->getMove(board);
auto *actual1 = new Move(2, 4, 3, 3, -1, -1, RED);
auto *actual2 = new Move(2, 4, 3, 5, -1, -1, RED);
auto *actual3 = new Move(2, 6, 3, 5, -1, -1, RED);
auto *actual4 = new Move(2, 6, 3, 7, -1, -1, RED);
bool returnMe = *expected == *actual1 || *expected == *actual2
        || *expected == *actual3 || *expected == *actual4;
REQUIRE(returnMe);
}
