//
// This class represents the board by holding the 24 pieces in a 2d-array
//
// Created by Luke on 1/28/2019.
//

#ifndef CHECKERS_01_BOARD_H
#define CHECKERS_01_BOARD_H

#include <vector>
#include <set>
#include "Checker.h"
#include "Move.h"

class Board {
private:
    // Count of red and black pieces
    int redCount = 12;
    int blackCount = 12;
    // Data structure representing the board
    Checker* grid[8][8] = {nullptr};

    // red and black pieces on the board
    std::set<Checker*>* redPieces = new std::set<Checker*>();
    std::set<Checker*>* blackPieces = new std::set<Checker*>();

public:
    /**
     * Constructs a board with pieces ready for play
     */
    Board();

    /**
     * @return a vector containing pointers to the red checkers still in play
     */
    std::set<Checker*>* getRedPieces();

    /**
     * @return a vector containing pointers to the black checkers still in play
     */
    std::set<Checker*>* getBlackPieces();

    /**
     * Returns the piece at the space at the row and column indicated by parameters. Does not check if there is
     * a piece at the space
     * @param row
     * @param col
     * @return a pointer to the checker at the space requested
     */
    Checker* getAt(int row, int col);

    /**
     * Returns true if there is a piece at the ath row nth and column
     * @param row
     * @param col
     * @return true if there is a piece at the space
     */
    bool contains(int row, int col);

    /**
     * moves a piece from one row and column to another
     * @param move
     */
    void move(Move* move);

    /**
     * Print the board to terminal
     */
    void printBoard();

    int getRedCount();
    int getBlackCount();
};


#endif //CHECKERS_01_BOARD_H
