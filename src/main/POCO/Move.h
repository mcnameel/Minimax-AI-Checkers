//
// Created by Luke on 1/28/2019.
//

#ifndef MINIMAX_AI_CHECKERS_MOVE_H
#define MINIMAX_AI_CHECKERS_MOVE_H

#include <string>
#include "../misc/Color.h"

/**
 * This class is a simple data object which represents a move. A move can
 * either be a simple move which is one space or a capture/jump which is two
 * spaces over an opponents piece
 */
class Move {

private:
    /* field vars */
    int destRow;
    int destCol;
    int curRow;
    int curCol;
    Color color;
    // initialize to  -1 which indicates that the move is not a jump/capture
    int capRow = -1;
    int capCol = -1;
    bool isKing = false;
    // true if the player has to jump multiple times
    Move* chainMove = nullptr;
public:
    /* constructors, destructor, and copy*/
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
     * delete the chainMove if it is not null
     */
    ~Move();

    Move* copy();

    /* util functions */
    std::string toString();
    bool operator==(const Move& m);

    /* accessors and mutators */
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
};

#endif //MINIMAX_AI_CHECKERS_MOVE_H
