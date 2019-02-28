//
// Created by Luke on 1/31/2019.
//

#include <iostream>
#include <set>
#include <algorithm>
#include "Rules.h"
#include "misc/Player.h"

bool Rules::playableSpaces[8][8] = {{true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true},
                                    {true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true},
                                    {true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true},
                                    {true, false, true, false, true, false, true, false},
                                    {false, true, false, true, false, true, false, true}};

bool Rules::legalMove(Move *move, Board *boardState) {
    std::vector<Move *> *requiredCaps = getJumps(boardState);
    bool legalMove = true;
    if (!requiredCaps->empty()){
        if(isCapture(move)) {
            if (!validCapture(move, boardState)) {
                std::cout << "You must make a legal capture" << std::endl;
                legalMove = false;
            } else {
                legalMove = requiredMultiCapture(move, boardState);
            }
        } else {
            legalMove = false;
            std::cout << "You must capture if able" << std::endl;
        }
    } else if (!validSpace(move->getDestRow(), move->getDestCol(), boardState)
               || !validMove(move, boardState)
               || !legalDirection(move, boardState)) {
        legalMove = false;
        std::cout << "invalid space" << std::endl;
    }
    if(!move->getKingMove()){
        move->setKingMove(shouldCrown(move));
    }
    delete requiredCaps;
    return legalMove;
}

bool Rules::validSpace(int row, int col, Board* boardState) {
    return playableSpaces[row][col] && !boardState->contains(row, col);
}

bool Rules::validCapture(Move *move, Board* boardState) {
    //std::cout << move->toString() << std::endl;
    /* bool returnMe = (validSpace(move->getDestRow(), move->getDestCol(), boardState) &&
      playableSpaces[move->getCapRow()][move->getCapCol()] &&
      boardState->contains(move->getCapRow(), move->getCapCol()) &&
      move->getColor() != boardState->getAt(move->getCapRow(), move->getCapCol())->getColor());
     std::cout << validSpace(move->getDestRow(), move->getDestCol(), boardState) << " part 1" << std::endl;
     std::cout << playableSpaces[move->getCapRow()][move->getCapCol()] << " part 2" << std::endl;
     std::cout <<  boardState->contains(move->getCapRow(), move->getCapCol()) << " part 3" << std::endl;
     std::cout << (move->getColor() != (boardState->getAt(move->getCapRow(), move->getCapCol())->getColor())) << " part 4" << std::endl;
     std::cout << ((boardState->getAt(move->getCapRow(), move->getCapCol())->getColor())) << " part 4" << std::endl;
     std::cout << (move->getColor()) << " part 4" << std::endl;
     std::cout << "RED "<< RED << std::endl;
     std::cout << "WHITE " << WHITE << std::endl;
    */
    bool returnMe = true;
    if (!validSpace(move->getDestRow(), move->getDestCol(), boardState)) {
        returnMe = false;
    } else if (!Rules::playableSpaces[move->getCapRow()][move->getCapCol()]) {
        returnMe = false;
    } else if (boardState->contains(move->getCapRow(), move->getCapCol())) {
        if (move->getColor() == boardState->getAt(move->getCapRow(), move->getCapCol())->getColor()) {
            returnMe = false;
        }
    } else
        returnMe = false;

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

std::vector<Move *> *Rules::getJumpsAtPos(Board *boardState, Checker *checker) {
    auto * returnMe = new std::vector<Move*>();
    int row = checker->getRow();
    int col = checker->getCol();
    Color color = checker->getColor();

    // check the possible moves for a player1 piece, else check for player2
    if(color == RED) {
        returnMe = getDownJumps(row, col, boardState);
        if(checker->isKing()) {
            returnMe = combine(returnMe, getUpJumps(row, col, boardState));
        }
    } else {
        // do the same with player2 but in the opposite direction
        returnMe = getUpJumps(row, col, boardState);
        if(checker->isKing())
            returnMe = combine(returnMe, getDownJumps(row, col, boardState));
    }
    // holds the jumps successor jumps of each move
    auto* successorJumps = new std::vector<Move*>();
    // hols the jumps that have a next jump available but do not have them added yet
    auto* incompleteJumps = new std::vector<Move*>();
    // for each jump that is found check if that jump has a multicapture available
    for(auto &jump: *returnMe) {
        //create a fake checker which is used to check if there is a capture available
        auto * mockChecker = new Checker(jump->getColor(), jump->getDestRow(), jump->getDestCol());
        // for the current jump get all of the jumps it has available
        auto * jumps = getJumpsAtPos(boardState, mockChecker);
        // if the move has next jump available add the incomplete jump to the
        // vector and get all the jumps available to it
        if(!jumps->empty()) {
            incompleteJumps->push_back(jump);
            for (auto &nextJump : *jumps) {
                Move* jumpCopy = jump->copy();
                jumpCopy->setChainMove(nextJump);
                successorJumps->push_back(jumpCopy);
            }
        }
        delete mockChecker;
    }
    // for each jump that has a multijump available that has not been found yet
    // remove this jump from the return list
    for(auto &incJump : *incompleteJumps) {
        auto e = std::find(returnMe->begin(), returnMe->end(), incJump);
        if (e != returnMe->end()) {
            returnMe->erase(e);
        }
    }
    returnMe = combine(returnMe, successorJumps);

    return returnMe;
}

std::vector<Move *>* Rules::getUpJumps(int row, int col, Board* boardState) {
    auto* returnMe = new std::vector<Move *>();
    Color color = boardState->getTurn();

    // Upper left move
    Move *ULMove = new Move(row, col, row + 2, col - 2,
                            row + 1, col - 1, color);
    // Upper right move
    Move *URMove = new Move(row, col, row + 2, col + 2,
                            row + 1, col + 1, color);
    if (validCapture(ULMove, boardState)) {
        returnMe->push_back(ULMove);
    } else
        delete ULMove;
    if (validCapture(URMove, boardState)) {
        returnMe->push_back(URMove);
    } else
        delete URMove;

    return returnMe;
}

std::vector<Move *> * Rules::getDownJumps(int row, int col, Board *boardState) {
    auto* returnMe = new std::vector<Move*>();
    Color color = boardState->getTurn();

    // Lower left move
    Move* LLMove = new Move(row, col, row - 2, col - 2,
                            row - 1, col - 1, color);
    // Lower right move
    Move* LRMove = new Move(row, col, row - 2, col + 2,
                            row - 1, col + 1, color);

    // if it is a valid capture then add it to the set of moves
    if(validCapture(LLMove, boardState)) {
        returnMe->push_back(LLMove);
    } else
        delete LLMove;
    if(validCapture(LRMove, boardState)) {
        returnMe->push_back(LRMove);
    } else
        delete LRMove;

    return returnMe;
}

std::vector<Move*>* Rules::combine(std::vector<Move*>* vec1, std::vector<Move*>* vec2) {
    for(auto &move : *vec2) {
        vec1->push_back(move);
    }

    return vec1;
}


std::vector<Move*>* Rules::getJumps(Board* boardState) {
    std::vector<Checker*>* pieces;
    if(boardState->getTurn() == RED ) {
        pieces = boardState->getRedPieces();
    } else {
        pieces = boardState->getWhitePieces();
    }

    // set to hold pointers to the required moves
    auto * returnMe = new std::vector<Move*>();
    // iterate through each piece and check if any of its moves is a capture
    for (auto &piece : *pieces) {
        auto* jumps = getJumpsAtPos(boardState, piece);
        for (auto &jump : *jumps) {
            returnMe->push_back(jump);
        }
        delete jumps;
    }
    return returnMe;
}

bool Rules::validMultiCapture(Move *move, Board* boardState) {
    Move* newMove = move->getChainMove();
    bool legal = (newMove != nullptr) && (isCapture(newMove) && validCapture(newMove, boardState) &&
            move->getDestRow() == newMove->getCurRow() &&
            move->getDestCol() == newMove->getCurCol());

    return legal;
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
        auto *jumps = getJumpsAtPos(boardState, piece);
        // now need a function to
        for (auto &jump : *jumps) {
            returnMe->push_back(jump);
        }
    }
    if (returnMe->empty()) {
        for (auto &piece : *pieces) {
            auto *moves = getMovesAtPos(piece->getRow(), piece->getCol(), boardState);
            for (auto &move : *moves) {
                returnMe->push_back(move);
            }
        }
        //delete jumps;
    }

    return returnMe;

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
    auto* returnMe = new std::vector<Move *>();
    Color color = boardState->getTurn();

    // Upper left move
    Move *ULMove = new Move(row, col, row + 1, col - 1, color);
    // Upper right move
    Move *URMove = new Move(row, col, row + 1, col + 1, color);
    if (validMove(ULMove, boardState) && legalDirection(ULMove, boardState)) {
        returnMe->push_back(ULMove);
    } else {
        delete ULMove;
    }
    if (validMove(URMove, boardState)&& legalDirection(URMove, boardState)) {
        returnMe->push_back(URMove);
    } else {
        delete URMove;
    }
    return returnMe;
}

std::vector<Move*>* Rules::getDownMoves(int row, int col, Board* boardState) {
    auto *returnMe = new std::vector<Move *>();
    Color color = boardState->getTurn();

    // Lower left move
    Move *LLMove = new Move(row, col, row - 1, col - 1, color);
    // Lower right move
    Move *LRMove = new Move(row, col, row - 1, col + 1, color);

    // if it is a valid capture then add it to the set of moves
    if (validMove(LLMove, boardState)&& legalDirection(LLMove, boardState)) {
        returnMe->push_back(LLMove);
    } else
        delete LLMove;
    if (validMove(LRMove, boardState) && legalDirection(LRMove, boardState)) {
        returnMe->push_back(LRMove);
    } else
        delete LRMove;

    return returnMe;
}

bool Rules::validMove(Move* move, Board* boardState) {
    bool legalMove = true;
    int curRow = move->getCurRow();
    int curCol = move->getCurCol();
    int destRow = move->getDestRow();
    int destCol = move->getDestCol();
    legalMove = ((curRow - 1 == destRow) || curRow + 1 == destRow)
                && ((curCol + 1 == destCol) || (curCol - 1 == destCol));

    if (!validSpace(destRow, destCol, boardState)) {
        legalMove = false;
    }
    return legalMove;
}

bool Rules::legalMoveFromColor(Move *move, Board *boardState) {
    bool legalMove = true;
    Color turn = boardState->getTurn();

    if (boardState->contains(move->getCurRow(), move->getCurCol())
        && turn != boardState->getAt(move->getCurRow(), move->getCurCol())->getColor()) {
        legalMove = false;
        std::cout << "not your turn" << std::endl;
    }
    return (legalMove && Rules::legalMove(move, boardState));
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

bool Rules::requiredMultiCapture(Move *move, Board *boardState) {
    bool legal = true;
    auto * mockChecker = new Checker(move->getColor(), move->getDestRow(), move->getDestCol());
    std::vector<Move *> *multiJumps = getJumpsAtPos(boardState, mockChecker);
    bool hasJumps = !multiJumps->empty();
    bool crowned = shouldCrown(move);
    // if there is a pointer to a multicapture in move and there are jumps to
    // make and the piece was not crowned this turn
    // Case: legal = false
    if ((validMultiCapture(move, boardState) && hasJumps) && !crowned) {
        legal = requiredMultiCapture(move->getChainMove(), boardState);
    }
    // else if there is no pointer to a multicap and there are no available
    // jumps or the piece has been crowned this turn
    // case: legal = true
    else if(move->getChainMove() == nullptr && (!hasJumps || crowned)) {
        legal = true;
    }
    // else any other case is invalid
    else {
        std::cout << "You must make a legal multiCapture" << std::endl;
        legal = false;
    }
    multiJumps->clear();
    delete mockChecker, multiJumps;
    return legal;
}

int Rules::numRequiredCaps(Move *m, Board *boardState) {
    return 0;
}

std::vector<Move *>* Rules::copy(std::vector<Move *>* vector) {
    auto * copy = new std::vector<Move *>();
    for(auto &move : *vector) {
        copy->push_back(move->copy());
    }
    return copy;
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
