//
// Created by Luke on 3/4/2019.
//

#include "tests-Board.h"
#include "../../Catch2/catch.hpp"
/*
//#define CATCH_CONFIG_MAIN
//#include "../../Catch2/Catch2.hpp"
//#include "../main/Rules.h"
// Test Case 1, ensure constructors work
TEST_CASE("First Test case") {
    bool success = true;
 /*   Board* board1 = new Board();
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
                whitePieces->push_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
                // the player1 pieces go from rows 1-3
            else if(i > 4) {
                // add a player1 piece to the board and to the container set
                Checker* c = new Checker(RED, i, 2 * j + (i % 2));
                redPieces->push_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
        }
    }
    std::vector<Checker*> * pieces = new std::vector<Checker*>();
    for(auto &piece : *redPieces) {
        pieces->push_back(piece);
    }
    for(auto &piece : *whitePieces) {
        pieces->push_back(piece);
    }

    Board* board2 = new Board(pieces, RED);

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
*
    REQUIRE(success);
}

TEST_CASE("Second Test case") {
    REQUIRE(1 != 0);
}

*/
