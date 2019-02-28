//
// This class is a simple data object which represents a move. A move can
// either be a simple move which is one space or a capture/jump which is two
// spaces over an opponents piece
//
// Created by Luke on 1/28/2019.
//

#ifndef CHECKERS_01_MOVE_H
#define CHECKERS_01_MOVE_H

#include <string>
#include "../misc/Color.h"

class Move {
private:
    /* vars */
    int destRow;
    int destCol;
    int curRow;
    int curCol;
    Color color;
    // initialize to  -1 which indicates that the move is not a jump/capture
    int capRow = -1;
    int capCol = -1;
    bool isKing = false;
    bool mustChainCapture = false;
    // true if the player has to jump multiple times
    Move* chainMove = nullptr;
public:
    void setMustChainCapture(bool mustChainCapture);
    bool isMustChainCapture() const;

    /**
     * Initialize an object move which is not a jump
     * @param curRow
     * @param curCol
     * @param destRow
     * @param destCol
     * @param color
     */
    Move(int curRow, int curCol, int destRow, int destCol, Color color);

    /**
     * Initialize an object of move which is a jump
     * @param curRow
     * @param curCol
     * @param destRow
     * @param destCol
     * @param capRow
     * @param capCol
     * @param color
     */
    Move(int curRow, int curCol, int destRow, int destCol, int capRow,
            int capCol, Color color);

    /**
     * Overload the == operator to check if the move matches the another
     * @param m
     * @return true if they are equal
     */
    bool operator==(const Move& m);

    int getCurRow();
    int getCurCol();
    int getDestRow();
    int getDestCol();
    Color getColor();
    int getCapRow();
    int getCapCol();
    void setCapSpace(int row, int col);
    void setKingMove(bool isKing);
    bool getKingMove();
    Move* getChainMove();
    void setChainMove(Move* m);

    Move* copy();

    std::string toString();
};

#endif //CHECKERS_01_MOVE_H
