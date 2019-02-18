//
// Created by Luke on 1/31/2019.
//

#include <iostream>
#include <set>
#include "Rules.h"

Rules::Rules(Board *board) {
    this->board = board;

    // create a 2d array to mimic the board which is used to check which
    // spaces are valid
    // iterate through each row on the board putting every other space as a
    // valid playable space and alternating which the first space of every row
    for(int i = 0; i < 8; ++i)
        // iterate through each column to add the piece. For each column
        // multiply j by two then add the modulus of i to get the offset for
        // each odd column.
        for (int j = 0; j < 4; ++j)
            playableSpaces[i][2 * j + (i % 2)] = true;
}

bool Rules::legalMove(Move *move, char turn) {
    bool legalMove = true;
    std::set<Move *> *requiredCaps = requiredCaptures(turn);

    if (turn != board->getAt(move->getCurRow(), move->getCurCol())->getColor()) {
        legalMove = false;
        std::cout << "not your turn" << std::endl;
    } else std::cout << turn << " " << move->getColor() << std::endl;
    if (!requiredCaps->empty()){
        if(isCapture(move)) {
            if (!validCapture(move)) {
                std::cout << "You must make a legal move" << std::endl;
                legalMove = false;
            }
        } else {
            legalMove = false;
            std::cout << "You must capture if able" << std::endl;
        }
    }
    if (!validSpace(move->getDestRow(), move->getDestCol())) {
        legalMove = false;
        std::cout << "invalid space" << std::endl;
    }

    return legalMove;
}

bool Rules::validSpace(int row, int col) {
    return playableSpaces[row][col] && !board->contains(row, col);
}

// TODO
bool Rules::canChain(Move *move) {
    bool returnMe = false;
    int curRow = move->getDestRow();
    int curCol = move->getDestCol();
    // Upper left space to jump to
    int ULDestRow = curRow + 2;
    int ULDestCol = curCol - 2;

    // Upper right space to jump to
    int URDestRow = curRow + 2;
    int URDestCol = curCol + 2;

    if(!(playableSpaces[ULDestRow][ULDestCol] ||
         playableSpaces[URDestRow][URDestCol])) {
        returnMe = false;
    }// else if()

    // Upper left space to jump over
    int ULRow = curRow - 1;
    int ULCol = curCol - 1;
    // Upper right space
    int URRow = curRow + 1;
    int URCol = curCol + 1;

//    if(board->contains(ULRow, ULCol))

    return false;
}

bool Rules::validPlayer(Move *move, char curTurn) {
    return (curTurn == move->getColor());
}

bool Rules::validCapture(Move *move) {
    bool returnMe = (validSpace(move->getDestRow(), move->getDestCol()) &&
     playableSpaces[move->getCapRow()][move->getCapCol()] &&
     board->contains(move->getCapRow(), move->getCapCol()) &&
     move->getColor() !=
        board->getAt(move->getCapRow(), move->getCapCol())->getColor());
    return returnMe;
}

// TODO: decide if function is needed
bool Rules::mustCapture(int curRow, int curCol, char color) {
    bool returnMe = false;

    // Upper left space to jump to
    int ULDestRow = curRow + 2;
    int ULDestCol = curCol - 2;

    // Upper right space to jump to
    int URDestRow = curRow + 2;
    int URDestCol = curCol + 2;

    // Upper left space to jump to
    int ULCapRow = curRow + 1;
    int ULCapCol = curCol - 1;

    // Upper right space to jump to
    int URCapRow = curRow + 1;
    int URCapCol = curCol + 1;

    if(!((validSpace(ULDestRow, ULDestCol) &&
          playableSpaces[ULCapRow][ULCapCol]) ||
         (validSpace(URDestRow, URDestCol) &&
          playableSpaces[ULCapRow][ULCapCol]))) {
        returnMe = false;
    }

    if(board->getAt(curRow, curCol)->isKing()) {
        // Lower left space to jump to
        int LLDestRow = curRow - 2;
        int LLDestCol = curCol - 2;

        // Lower right space to jump to
        int LRDestRow = curRow - 2;
        int LRDestCol = curCol + 2;

        // Lower left space to jump to
        int LLCapRow = curRow - 1;
        int LLCapCol = curCol - 1;

        // Lower right space to jump to
        int LRCapRow = curRow - 1;
        int LRCapCol = curCol + 1;

        if(!((validSpace(LLDestRow, LLDestCol) &&
              validSpace(LLCapRow, LLCapCol)) ||
             (validSpace(LRDestRow, LRDestCol) &&
              validSpace(LLCapRow, LLCapCol)))) {
            returnMe = false;
        }
    }
    return false;
}

// TODO: clean up this function
std::set<Move*>* Rules::requiredCaptures(char color) {
    // set to hold pointers to the required moves
    std::set<Move*>* returnMe = new std::set<Move*>();
    std::set<Checker*> pieces;

    // iterate through each piece and check if any of its moves is a capture
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        checkCaptures(*it, returnMe);
    }
    return returnMe;
}

bool Rules::isCapture(Move *m) {
    // 5 cases with only 1 false so assume the output true
    bool returnMe = true;

    int curRow = m->getCurRow();
    int curCol = m->getCurCol();

    int destRow = m->getDestRow();
    int destCol = m->getDestCol();

    // Check if the piece is moving two spaces and if it is then set the
    // capture accordingly
    if(curRow - destRow == - 2 && curCol - destCol == - 2)
        m->setCapSpace(curRow + 1, curCol + 1);
    else if(curRow - destRow == 2 && curCol - destCol == 2)
        m->setCapSpace(curRow - 1, curCol - 1);
    else if(curRow - destRow == - 2 && curCol - destCol == 2)
        m->setCapSpace(curRow + 1, curCol - 1);
    else if(curRow - destRow == 2 && curCol - destCol == - 2)
        m->setCapSpace(curRow - 1, curCol + 1);
    else
        returnMe = false;

    return returnMe;
}

bool Rules::checkCaptures(Checker *c, std::set<Move*>* captures) {
    std::set<Checker*> pieces = (c->getColor() == 'b')
            ? *(board->getBlackPieces()) : *(board->getRedPieces());

    bool returnMe = false;
    // get the current location of the piece
    int row = c->getRow();
    int col = c->getCol();

    // check the possible moves for a black piece, else check for red
    if(c->getColor() == 'b') {
        checkDownMoves(c, captures);
        if(c->isKing())
            checkUpMoves(c, captures);

    } else {
        // do the same with red but in the opposite direction
        checkUpMoves(c, captures);

        if(c->isKing())
            checkDownMoves(c, captures);
    }
    return returnMe;
}

bool Rules::checkDownMoves(Checker *c, std::set<Move *> *captures) {
    bool returnMe = false;

    int row = c->getRow();
    int col = c->getCol();

    // Lower left move
    Move* LLMove = new Move(row, col, row - 2, col - 2,
                            row - 1, col - 1, c->getColor());
    // Lower right move
    Move* LRMove = new Move(row, col, row - 2, col + 2,
                            row - 1, col + 1, c->getColor());

    // if it is a valid capture then add it to the set of moves
    if(validCapture(LLMove)) {
        captures->insert(LLMove);
        returnMe = true;
    } else
        delete LLMove;
    if(validCapture(LRMove)) {
        captures->insert(LRMove);
        returnMe = true;
    } else
        delete LRMove;
    // if the piece is a king then check the moves in all directions

    return returnMe;
}

bool Rules::checkUpMoves(Checker *c, std::set<Move *> *captures) {
    bool returnMe = false;

    int row = c->getRow();
    int col = c->getCol();

    // Upper left move
    Move *ULMove = new Move(row, col, row + 2, col - 2,
                            row + 1, col - 1, c->getColor());
    // Upper right move
    Move *URMove = new Move(row, col, row + 2, col + 2,
                            row + 1, col + 1, c->getColor());
    if (validCapture(ULMove)) {
        captures->insert(ULMove);
        returnMe = true;
    } else
        delete ULMove;
    if (validCapture(URMove)) {
        captures->insert(URMove);
        returnMe = true;
    } else
        delete URMove;

    return returnMe;
}
