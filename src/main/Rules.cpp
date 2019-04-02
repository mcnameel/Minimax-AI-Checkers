//
// Created by Luke on 1/31/2019.
//

#include <iostream>
#include <set>
#include <algorithm>
#include "../../include/internal/Rules.h"
#include "../../include/internal/Player.h"

bool Rules::playableSpaces[8][8] = {{true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true},
                                    {true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true},
                                    {true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true},
                                    {true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true}};

bool Rules::legalMove(Move *move, Board *boardState) {
    bool legalMove = false;
    std::vector<Move *> *possibleMoves = getAllLegalMoves(boardState);
    Move* temp = move;
    while(temp != nullptr) {
        isCapture(temp);
        temp = temp->getNextChainMove();
    }
    for(auto &posMove : *possibleMoves) {
        if(*posMove == *move) {
            legalMove = true;
        }
    }
    if(!move->getKingMove()){
        shouldCrown(move);
    }
    for(int i = 0; i < possibleMoves->size(); ++i) {
        delete (*possibleMoves)[i];
    }
    delete possibleMoves;
    return legalMove;
}

std::vector<Move*>* Rules::getAllLegalMoves(Board* boardState) {
    auto *returnMe = new std::vector<Move *>();
    std::vector<Checker *> *pieces;
    // if the last move was red get the white pieces else vice versa
    if (boardState->getTurn() == RED) {
        pieces = boardState->getRedPieces();
    } else {
        pieces = boardState->getWhitePieces();
    }
    // iterate through each piece and check if any of its moves is a capture
    for (auto &piece : *pieces) {
        auto *jumps = getAllJumpsAtPos(boardState, piece);
        // now need a function to
        for (auto &jump : *jumps) {
            returnMe->push_back(jump);
        }
        delete jumps;
    }
    if (returnMe->empty()) {
        for (auto &piece : *pieces) {
            auto *moves = getMovesAtPos(piece->getRow(), piece->getCol(), boardState);
            for (auto &move : *moves) {
                returnMe->push_back(move);
            }
            delete moves;
        }
    }
    return returnMe;
}

std::vector<Move *> *Rules::getAllJumpsAtPos(Board *boardState, Checker *checker) {
    static int counter = 0;
    counter++;
    auto *returnMe = getJumpsAtPos(boardState, checker);

    // holds the jumps successor jumps of each move
    auto* successorJumps = new std::vector<Move*>();
    // hols the jumps that have a next jump available but do not have them added yet
    std::vector<Move*> incompleteJumps;

    // for each jump that is found check if that jump has a multicapture available
    for(auto &jump: *returnMe) {
        Board* boardCopy = boardState->copy();
        // push the jump to the mock board
        boardCopy->move(jump, false);

        //create a fake checker which is used to check if there is a capture available
        auto * mockChecker = boardCopy->getAt(jump->getDestRow(), jump->getDestCol())->copy();

        // for the current jump get all of the jumps it has available
        std::vector<Move *> * jumps;
        if(jump->getKingMove()) {
            jumps = new std::vector<Move*>();
        } else {
            jumps = getAllJumpsAtPos(boardCopy, mockChecker);
        }
        // if the move has next jump available add the incomplete jump to the
        // vector and get all the jumps available to it
        if(!jumps->empty()) {
            incompleteJumps.push_back(jump);
            for (auto &nextJump : *jumps) {
                Move* jumpCopy = jump->copy();
                jumpCopy->setNextChainMove(nextJump);
                successorJumps->push_back(jumpCopy);
            }
        }
        delete boardCopy;
        delete mockChecker;
        delete jumps;
    }
    // for each jump that has a multijump available that has not been found yet
    // remove this jump from the return list
    for(int i = 0; i < incompleteJumps.size(); ++i) {
        Move *incJump = incompleteJumps[i];
        for(int j = 0; j < returnMe->size(); ++j) {
            Move *jump = (*returnMe)[j];
            if(*jump == *incJump) {
                delete jump;
                returnMe->erase(returnMe->begin() + j);
            }
        }
    }
    returnMe = combine(returnMe, successorJumps);
    delete successorJumps;

    return returnMe;
}

std::vector<Move *> *Rules::getJumpsAtPos(Board *boardState, Checker *checker) {
    Color color = checker->getColor();
    auto *returnMe = new std::vector<Move*>();

    // check the possible moves for a player1 piece, else check for player2
    if(color == RED) {
        Move *LLJump = getLLJump(checker, boardState);
        if(LLJump != nullptr) {
            returnMe->push_back(LLJump);
        }
        Move *LRJump = getLRJump(checker, boardState);
        if(LRJump != nullptr) {
            returnMe->push_back(LRJump);
        }
        if(checker->isKing()) {
            Move *ULJump = getULJump(checker, boardState);
            if(ULJump != nullptr) {
                returnMe->push_back(ULJump);
            }
            Move *URJump = getURJump(checker, boardState);
            if(URJump != nullptr) {
                returnMe->push_back(URJump);
            }
        }
    } else {
        // do the same with player2 but in the opposite direction
        Move *ULJump = getULJump(checker, boardState);
        if(ULJump != nullptr) {
            returnMe->push_back(ULJump);
        }
        Move *URJump = getURJump(checker, boardState);
        if(URJump != nullptr) {
            returnMe->push_back(URJump);
        }
        if(checker->isKing()) {
            Move *LLJump = getLLJump(checker, boardState);
            if (LLJump != nullptr) {
                returnMe->push_back(LLJump);
            }
            Move *LRJump = getLRJump(checker, boardState);
            if (LRJump != nullptr) {
                returnMe->push_back(LRJump);
            }
        }
    }
    return returnMe;
}

bool Rules::validSpace(int row, int col, Board* boardState) {
    return Rules::playableSpaces[row][col] && !boardState->contains(row, col);
}

bool Rules::validCapture(Move *move, Board* boardState) {
    int capCol = move->getCapCol();
    int capRow = move->getCapRow();
    bool returnMe = true;
    // if not a valid space on the board or the space is occupied
    if (!validSpace(move->getDestRow(), move->getDestCol(), boardState)) {
        returnMe = false;
    }
    // else if board contains a piece at the cap space
    else if (boardState->contains(capRow, capCol)) {
        // check that it is an opponents piece
        if (move->getColor() == boardState->getAt(capRow, capCol)->getColor()) {
            returnMe = false;
        }
    } else {
        returnMe = false;
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
    else {
        returnMe = false;
    }
    return returnMe;
}

std::vector<Move*>* Rules::combine(std::vector<Move*>* vec1, std::vector<Move*>* vec2) {
    for(auto &move : *vec2) {
        vec1->push_back(move);
    }

    return vec1;
}

bool Rules::validMultiCapture(Move *move, Board* boardState) {
    Move* newMove = move->getNextChainMove();
    bool legal = (newMove != nullptr) && (isCapture(newMove) && validCapture(newMove, boardState) &&
            move->getDestRow() == newMove->getCurRow() &&
            move->getDestCol() == newMove->getCurCol());

    return legal;
}

std::vector<Move*>* Rules::getMovesAtPos(int row, int col, Board* boardState) {
    auto * returnMe = new std::vector<Move*>();
    Checker* c = boardState->getAt(row, col);
    Color color = c->getColor();

    // check the possible moves for a player2 piece, else check for white
    if(color == RED) {
        returnMe = getDownMoves(row, col, boardState);
        if(c->isKing()) {
            returnMe = combine(returnMe, getUpMoves(row, col, boardState));
        }
    } else {
        // do the same with player2 but in the opposite direction
        returnMe = getUpMoves(row, col, boardState);
        if(c->isKing())
            returnMe = combine(returnMe, getDownMoves(row, col, boardState));
    }
    return returnMe;
}

std::vector<Move *>* Rules::getUpMoves(int row, int col, Board* boardState) {
    auto *returnMe = new std::vector<Move *>();
    Color color = boardState->getTurn();

    int upRow = row + 1;
    int rtCol = col + 1;
    int ltCol = col - 1;
    if (upRow < Board::getBOARDHEIGHT()) {
        if (ltCol >= 0) {
            int destRow = row + 1;
            int destCol = col - 1;
            // Upper left move
            Move *ULMove = new Move(row, col, destRow, destCol, -1, -1, color);
            crownMe(ULMove, boardState);
            if (validSpace(destRow, destCol, boardState)
                && legalDirection(ULMove, boardState)) {
                returnMe->push_back(ULMove);
            } else
                delete ULMove;
        }
        if(rtCol < Board::getBOARDWIDTH()) {
            int destRow = row + 1;
            int destCol = col + 1;
            // Upper right move
            Move *URMove = new Move(row, col, destRow, destCol, -1, -1, color);
            crownMe(URMove, boardState);
            if (validSpace(destRow, destCol, boardState) && legalDirection(URMove, boardState)) {
                returnMe->push_back(URMove);
            } else
                delete URMove;
        }
    }
    return returnMe;
}

std::vector<Move*>* Rules::getDownMoves(int row, int col, Board* boardState) {
    auto* returnMe = new std::vector<Move*>();
    Color color = boardState->getTurn();

    int downRow = row - 1;
    int rtCol = col + 1;
    int ltCol = col - 1;
    // if the column is >= 0 then it is valid
    if (downRow >= 0) {
        if (ltCol >= 0) {
            int destRow = row - 1;
            int destCol = col - 1;
            // Lower left move
            Move *LLMove = new Move(row, col, destRow, destCol,
                                    -1, -1, color);
            crownMe(LLMove, boardState);
            if (validSpace(destRow, destCol, boardState)
                && legalDirection(LLMove, boardState)) {
                returnMe->push_back(LLMove);
            } else
                delete LLMove;
        }
        if(rtCol < Board::getBOARDWIDTH()) {
            int destRow = row - 1;
            int destCol = col + 1;
            // Lower right move
            Move* LRMove = new Move(row, col, destRow, destCol,
                                    -1, -1, color);
            crownMe(LRMove, boardState);
            if (validSpace(destRow, destCol, boardState)
                && legalDirection(LRMove, boardState)) {
                returnMe->push_back(LRMove);
            } else
                delete LRMove;
        }
    }
    return returnMe;
}

bool Rules::legalMoveFromColor(Move *move, Board *boardState) {
    bool legalMove = true;
    Color turn = boardState->getTurn();
    
    if (boardState->contains(move->getCurRow(), move->getCurCol())
        && turn != boardState->getAt(move->getCurRow(), move->getCurCol())->getColor()) {
        legalMove = false;
        std::cout << "not your turn" << std::endl;
    }
    bool b = Rules::legalMove(move, boardState);
    
    return (legalMove && b);
}

bool Rules::shouldCrown(Move *move) {
    bool crowned = false;
    if((move->getDestRow() == 7 && move->getColor() == WHITE) ||
       (move->getDestRow() == 0 && move->getColor() == RED)) {
        move->setKingMove(true);
        crowned = true;
    }
    return crowned;
}

bool Rules::requiredMultiCapture(Move *move, Board *boardState, bool isKing) {
    bool legal = true;
    /* copy the board state and push the move through to the mock board */
    Board* boardCopy = boardState->copy();
    boardCopy->move(move, false);
    /* get a mock checker from where the piece lands */
    auto * mockChecker = new Checker(move->getColor(), move->getDestRow(), move->getDestCol());

    if(isKing)
        mockChecker->makeKing();

    std::vector<Move *> *multiJumps = getAllJumpsAtPos(boardCopy, mockChecker);
    bool hasJumps = !multiJumps->empty();
    bool crowned = false;
    if(!isKing) {
        crowned = shouldCrown(move);
        isKing = crowned;
    }

    // if there is a pointer to a multicapture in move and there are jumps to
    // make and the piece was not crowned this turn
    // Case: legal = false
    if ((validMultiCapture(move, boardCopy) && hasJumps) && !crowned) {
        legal = requiredMultiCapture(move->getNextChainMove(), boardCopy, isKing);
    }
    // else if there is no pointer to a multicap and there are no available
    // jumps or the piece has been crowned this turn
    // case: legal = true
    else legal = move->getNextChainMove() == nullptr && (!hasJumps || crowned);
    for (int i = 0; i < multiJumps->size(); ++i) {
        delete (*multiJumps)[i];
    }
    delete boardCopy;
    delete mockChecker;
    delete multiJumps;

    return legal;
}

bool Rules::legalDirection(Move *move, Board *boardState) {
    bool legalMove = true;
    int curRow = move->getCurRow();
    int destRow = move->getDestRow();
    if(move->getColor() == RED) {
        legalMove = (curRow - 1 == destRow);
    } else {
        legalMove = (curRow + 1 == destRow);
    }
    if(boardState->getAt(move->getCurRow(), move->getCurCol())->isKing()) {
        legalMove = true;
    }
    return legalMove;
}

bool Rules::crownMe(Move *move, Board *boardState) {
    bool crowned = false;
    Checker *checker = boardState->getAt(move->getCurRow(), move->getCurCol());

    if (!checker->isKing() &&
            ((move->getDestRow() == 7 && move->getColor() == WHITE)
            || (move->getDestRow() == 0 && move->getColor() == RED))) {
        move->setKingMove(true);
        crowned = true;
    }
    return crowned;
}



Move *Rules::getLLJump(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int downRow = row - 2;
    int ltCol = col - 2;
    if (downRow >= 0 && ltCol >= 0) {
        // Upper left move
        Move *LLMove = new Move(row, col, downRow, ltCol,
                                row - 1, col - 1, color);
        crownMe(LLMove, boardState);

        if (validCapture(LLMove, boardState)) {
            returnMe = LLMove;
        } else {
            delete LLMove;
        }
    }
    return returnMe;
}

Move *Rules::getLRJump(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int downRow = row - 2;
    int rtCol = col + 2;
    if (downRow >= 0 && rtCol <= Board::getBOARDWIDTH()) {
        Move *LRMove = new Move(row, col, downRow, rtCol,
                                row - 1, col + 1, color);
        crownMe(LRMove, boardState);

        if (validCapture(LRMove, boardState)) {
            returnMe = LRMove;
        } else {
            delete LRMove;
        }
    }
    return returnMe;
}

Move *Rules::getULJump(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int upRow = row + 2;
    int ltCol = col - 2;
    if (upRow <= Board::getBOARDHEIGHT() && ltCol >= 0) {
        // Upper left move
        Move *ULMove = new Move(row, col, upRow, ltCol,
                                row + 1, col - 1, color);
        crownMe(ULMove, boardState);

        if (validCapture(ULMove, boardState)) {
            returnMe = ULMove;
        } else {
            delete ULMove;
        }
    }
    return returnMe;
}

Move *Rules::getURJump(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int upRow = row + 2;
    int rtCol = col + 2;
    if (upRow <= Board::getBOARDHEIGHT() && rtCol <= Board::getBOARDWIDTH()) {
        Move *URMove = new Move(row, col, upRow, rtCol,
                                row + 1, col + 1, color);
        crownMe(URMove, boardState);

        if (validCapture(URMove, boardState)) {
            returnMe = URMove;
        } else {
            delete URMove;
        }
    }
    return returnMe;
}

Move *Rules::getLLMove(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int downRow = row - 1;
    int ltCol = col - 1;
    if (downRow >= 0 && ltCol >= 0) {
        int destRow = row - 1;
        int destCol = col - 1;
        // Lower left move
        Move *LLMove = new Move(row, col, destRow, destCol,
                                -1, -1, color);
        crownMe(LLMove, boardState);
        if (validSpace(destRow, destCol, boardState)
            && legalDirection(LLMove, boardState)) {
            returnMe = LLMove;
        } else
            delete LLMove;
    }
    return returnMe;
}

Move *Rules::getLRMove(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int downRow = row - 1;
    int rtCol = col + 1;
    if (downRow >= 0 && rtCol <= Board::getBOARDWIDTH()) {
        int destRow = row - 1;
        int destCol = col + 1;
        // Lower right move
        Move* LRMove = new Move(row, col, destRow, destCol,
                                -1, -1, color);
        crownMe(LRMove, boardState);
        if (validSpace(destRow, destCol, boardState)
            && legalDirection(LRMove, boardState)) {
            returnMe = LRMove;
        } else
            delete LRMove;
    }
    return returnMe;
}

Move *Rules::getULMove(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int upRow = row + 2;
    int ltCol = col - 2;
    if (upRow <= Board::getBOARDHEIGHT() && ltCol >= 0) {
        int destRow = row + 1;
        int destCol = col - 1;
        // Upper left move
        Move *ULMove = new Move(row, col, destRow, destCol, -1, -1, color);
        crownMe(ULMove, boardState);
        if (validSpace(destRow, destCol, boardState)
            && legalDirection(ULMove, boardState)) {
            returnMe = ULMove;
        } else
            delete ULMove;
    }
    return returnMe;
}

Move *Rules::getURMove(Checker *c, Board *boardState) {
    Move *returnMe = nullptr;
    Color color = c->getColor();
    int row = c->getRow();
    int col = c->getCol();
    int upRow = row + 2;
    int rtCol = col + 2;
    if (upRow <= Board::getBOARDHEIGHT() && rtCol <= Board::getBOARDWIDTH()) {
        int destRow = row + 1;
        int destCol = col + 1;
        // Upper right move
        Move *URMove = new Move(row, col, destRow, destCol, -1, -1, color);
        crownMe(URMove, boardState);
        if (validSpace(destRow, destCol, boardState) && legalDirection(URMove, boardState)) {
            returnMe = URMove;
        } else
            delete URMove;
    }
    return returnMe;
}