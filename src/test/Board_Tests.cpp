//
// Created by Luke McNamee on 2019-03-12.
//

#include "../../include/external/Catch2/single_include/catch2/catch.hpp"

//#define CATCH_CONFIG_MAIN
#include "../../include/internal/Rules.h"
#include "../../include/internal/AI_Evaluation_Impl_01.h"

// Test Case 1, ensure constructors work
TEST_CASE("First Test case") {
    bool success = true;
    Board* board1 = new Board();
    auto * whitePieces = new std::vector<Checker*>();
    auto * redPieces = new std::vector<Checker*>();
    Checker* grid[8][8] = {nullptr};
    for(int i = 0; i < 8; ++i) {
        // iterate through each column to add the piece. For each column
        // multiply j by two then add the modulus of i to get the offset for
        // each odd column.
        for (int j = 0; j < 4; ++j) {
            // the player2 pieces go from rows 1-3
            if(i < 3) {
                // add a player2 piece to the board and to the container set
                auto * c = new Checker(WHITE, i, 2 * j + (i % 2));
                whitePieces->emplace_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
                // the player1 pieces go from rows 1-3
            else if(i > 4) {
                // add a player1 piece to the board and to the container set
                Checker* c = new Checker(RED, i, 2 * j + (i % 2));
                redPieces->emplace_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
        }
    }
    std::vector<Checker*> * pieces = new std::vector<Checker*>();
    for(auto &piece : *redPieces) {
        pieces->emplace_back(piece);
    }
    for(auto &piece : *whitePieces) {
        pieces->emplace_back(piece);
    }

    Board* board2 = new Board(pieces, RED, nullptr, false);

    for(int i = 0; i < 8; ++i) {
        // iterate through each column to add the piece. For each column
        // multiply j by two then add the modulus of i to get the offset for
        // each odd column.
        for (int j = 0; j < 8; ++j) {
            Checker * c1 = board1->getAt(i, j);
            Checker * c2 = board2->getAt(i, j);
            if (c1 == nullptr || c2 == nullptr) {
                if (c1 != nullptr || c2 != nullptr) {
                    success = false;
                }
            } else if(!(*c1 == *c2)){
                success = false;
            }
        }
    }

    REQUIRE(success);
}

TEST_CASE("Second Test case") {
    REQUIRE(1 != 0);
}

/**
 * Case: it's RED's turn a they will loose on the turn after this
 * check that on that next turn the Board::isGameOver() == true
 *
  |-------------------------------|
7 |   |   |   |   |   |   |   | r |
  |-------------------------------|
6 |   |   |   |   | w |   | w |   |
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
   -------------------------------   White: 2
    a   b   c   d   e   f   g   h    Red:   1
Red's turn

 */
TEST_CASE("Game Over Case 1") {
    /*Checker* c1 = new Checker(RED, 7, 7);
    Checker* c2 = new Checker(WHITE, 6, 6);
    Checker* c3 = new Checker(WHITE, 6, 4);

    std::vector<Checker*>* pieces = new std::vector<Checker*>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);
    pieces->emplace_back(c3);

    Board* board = new Board(pieces, RED);
    board->printBoard();
    AI_Minimax_01* player1 = new AI_Minimax_01(2, RED);
    AI_Minimax_01* player2 = new AI_Minimax_01(2, WHITE);

    Move* m = player1->getMove(board);
    board->move(m, true);
    delete m;

    m = player2->getMove(board);
    board->move(m, true);

    m = player1->getMove(board);
    board->move(m, true);

    REQUIRE(board->isGameOver());
    */
}

/**
 * Check that when a piece is captured that it is removed from the Board::Grid
 @setup:
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
 TEST_CASE("Board::Move() | red piece removed from Board::grid") {
    /* setup */
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);
    auto pieces = new std::vector<Checker *>();
    pieces->emplace_back(c1);
    pieces->emplace_back(c2);
    auto *board = new Board(pieces, WHITE, nullptr, false);
    auto *move = new Move(5, 5, 7, 3, 6, 4, WHITE);
    move->setKingMove(true);

    /* testing */
    board->move(move, true);
    REQUIRE(!board->contains(6, 4));
 }
/**
 * Check that when a piece is captured that it is removed from the vector
 * holding the pieces of a specific color
 @setup:
   -----------
7 |   |   |   |
  |-----------|
6 |   | r |   |
  |-----------|
5 |   |   | w |
   -----------
    d   e   f
Red's turn
 */
 TEST_CASE("Board::Move() | red piece removed from Board::redPieces when king move") {
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);

    auto pieces = new std::vector<Checker *>();
    pieces->emplace_back(c1);
    pieces->emplace_back(c2);

    auto *board = new Board(pieces, WHITE, nullptr, false);
    auto *move = new Move(5, 5, 7, 3, 6, 4, WHITE);
    move->setKingMove(true);

    board->move(move, true);
    REQUIRE(board->getRedCount() == 0);
 }

/**
 * Check that when a piece is captured that it is removed from the Board::Grid
 @setup:
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
 TEST_CASE("Board::Move() | white piece removed from Board::grid") {
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);

    auto pieces = new std::vector<Checker *>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);

    auto *board = new Board(pieces, RED, nullptr, false);

    auto *move = new Move(6, 4, 4, 6, 5, 5, RED);

    board->move(move, true);
    REQUIRE(!board->contains(5, 5));
 }
/**
 * Check that when a piece is captured that it is removed from the Board::Grid
 @setup:
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
 TEST_CASE("Board::Move() | white piece removed from Board::whitePieces") {
    auto *c1 = new Checker(RED, 6, 4);
    auto *c2 = new Checker(WHITE, 5, 5);

    auto pieces = new std::vector<Checker *>();

    pieces->emplace_back(c1);
    pieces->emplace_back(c2);

    auto *board = new Board(pieces, RED, nullptr, false);

    auto *move = new Move(6, 4, 4, 6, 5, 5, RED);

    board->move(move, true);
    REQUIRE(board->getWhiteCount() == 0);
 }

