//
// This class is a simple data object which represents one checkers piece
//
// Created by Luke on 1/28/2019.
//

#ifndef MINIMAX_AI_CHECKERS_CHECKER_H
#define MINIMAX_AI_CHECKERS_CHECKER_H

#include <string>
#include "../misc/Color.h"

class Checker {

private:
    // vars
    Color COLOR;
    bool king = false;
    int row = 0;
    int col = 0;

public:
    bool operator==(const Checker& c);
    char getColorChar();
    Color getColor();
    /**
     * check if the checker has been kinged
     * @return true if the checker has been kinged
     */
    bool isKing();

    /**
     * Sets the checker to be a king
     */
    void makeKing();

    int getRow();
    void setRow(int r);
    int getCol();
    void setCol(int c);

    /**
     * Initializes a checker object. Color must be RED or WHITE
     * @param color
     * @param row
     * @param col
     */
    Checker(Color color, int row, int col);
    Checker(Color color, int row, int col, bool isKing);

    std::string toString();
    Checker* copy();
};

#endif //MINIMAX_AI_CHECKERS_CHECKER_H
