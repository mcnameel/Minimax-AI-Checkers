//
// Created by Luke on 1/28/2019.
//

#include "Board.h"
#include <iostream>

Board::Board() {
    // populate the board by iterating through the board, row then column,
    // to populate the board with pieces
    for(int i = 0; i < 8; ++i) {
        // iterate through each column to add the piece. For each column
        // multiply j by two then add the modulus of i to get the offset for
        // each odd column.
        for (int j = 0; j < 4; ++j) {
            // the red pieces go from rows 1-3
            if(i < 3) {
                // add a red piece to the board and to the container set
                Checker* c = new Checker('r', i, 2 * j + (i % 2));
                redPieces->insert(c);
                grid[i][2 * j + (i % 2)] = c;
            }
            // the black pieces go from rows 1-3
            else if(i > 4) {
                // add a black piece to the board and to the container set
                Checker* c = new Checker('b', i, 2 * j + (i % 2));
                blackPieces->insert(c);
                grid[i][2 * j + (i % 2)] = c;
            }
        }
    }
    // For testing purposes
  /*  Checker* c1 = new Checker('r', 4, 2);
    Checker* c2 = new Checker('b', 3, 1);

    grid[4][2] = c1;
    grid[3][1] = c2;

    redPieces->insert(c1);
    blackPieces->insert(c2);
*/}

void Board::printBoard() {
    for (int r = 7; r >= 0; r--) {
        std::cout << "  |-------------------------------|" << std::endl;
        std::cout << r << " ";
        for (int c = 0; c < 8; c++) {
            std::cout << "|";
            if (grid[r][c] != nullptr)
                std::cout << " " << grid[r][c]->getColor() << " ";
            else std::cout << "   ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   -------------------------------   ";
    std::cout << "black: " << getBlackPieces()->size() << std::endl;
    std::cout << "    a   b   c   d   e   f   g   h    ";
    std::cout << "red:   " << getRedPieces()->size() << std::endl;


}

bool Board::contains(int row, int col) {
    return (grid[row][col] != nullptr);
}

Checker* Board::getAt(int row, int col) {
    return grid[row][col];
}

void Board::move(Move *move) {
    Checker* c = grid[move->getCurRow()][move->getCurCol()];
    // remove the piece from the starting space then move it to the next
    grid[move->getCurRow()][move->getCurCol()] = nullptr;
    grid[move->getDestRow()][move->getDestCol()] = c;

    // set the destination vars
    c->setRow(move->getDestRow());
    c->setCol(move->getDestCol());

    // if the move is a king move then set the piece to be a king
    if(move->getKingMove())
        c->makeKing();

    // Check if piece should be deleted
    if (move->getCapCol() != -1) {
        Checker * cap = grid[move->getCapRow()][move->getCapCol()];
        grid[move->getCapRow()][move->getCapCol()] = nullptr;
        if(move->getColor() == 'b') {
            redPieces->erase(cap);
            --redCount;
        } else {
            blackPieces->erase(cap);
            --blackCount;
        }
        //delete cap;
    }
}

std::set<Checker*>* Board::getRedPieces() {
    return redPieces;
}

std::set<Checker*>* Board::getBlackPieces() {
    return blackPieces;
}

int Board::getRedCount() {
    return redPieces->size();
}

int Board::getBlackCount() {
    return blackPieces->size();
}
