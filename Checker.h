//
// This class is a simple data object which represents one checkers piece
//
// Created by Luke on 1/28/2019.
//

#ifndef CHECKERS_01_CHECKER_H
#define CHECKERS_01_CHECKER_H


class Checker {

private:
    // vars
    char COLOR;
    bool king = false;
    int row = 0;
    int col = 0;

public:
    char getColor();
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
     * Initializes a checker object. Color must be 'r' or 'b'
     * @param color
     * @param row
     * @param col
     */
    Checker(char color, int row, int col);
};

#endif //CHECKERS_01_CHECKER_H
