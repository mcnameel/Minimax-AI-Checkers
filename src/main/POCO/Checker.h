//
// Created by Luke on 1/28/2019.
//

#ifndef MINIMAX_AI_CHECKERS_CHECKER_H
#define MINIMAX_AI_CHECKERS_CHECKER_H

#include <string>
#include "../misc/Color.h"
/*
 * This class is a simple data object which represents one checkers piece
 */
class Checker {

private:
    /* field vars */
    Color COLOR;
    bool king = false;
    int row = 0;
    int col = 0;

public:
    /* constructors and copy */
    /**
     * Initializes a checker object. Color must be RED or WHITE
     * @param color
     * @param row
     * @param col
     */
    Checker(Color color, int row, int col);
    Checker* copy();

    /* util method */
    std::string toString();
    bool operator==(const Checker& c);


    /* accessors and mutators */
    char getColorChar();
    Color getColor();
    bool isKing();
    /**
     * Sets the checker to be a king
     */
    void makeKing();
    int getRow();
    void setRow(int r);
    int getCol();
    void setCol(int c);

};

#endif //MINIMAX_AI_CHECKERS_CHECKER_H
