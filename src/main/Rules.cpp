//
// Created by Luke on 1/31/2019.
//

#include <iostream>
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
    for(auto & possibleMove : *possibleMoves) {
        delete possibleMove;
    }
    delete possibleMoves;
    return legalMove;
}

std::vector<Move*>* Rules::getAllJumpsForPlayer(Board *boardState) {
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
            returnMe->emplace_back(jump);
        }
        delete jumps;
    }
    return returnMe;
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
            returnMe->emplace_back(jump);
        }
        delete jumps;
    }
    // if returnMe is empty then there were no legal jumps to make so get all moves
    if (returnMe->empty()) {
        for (auto &piece : *pieces) {
            auto *moves = getMovesAtPos(piece, boardState);
            for (auto &move : *moves) {
                returnMe->emplace_back(move);
            }
            delete moves;
        }
    }
    return returnMe;
}

std::vector<Move *> *Rules::getAllJumpsAtPos(Board *boardState, Checker *checker) {
    auto *returnMe = getJumpsAtPos(boardState, checker);

    // holds the jumps successor jumps of each move
    auto* successorJumps = new std::vector<Move*>();
    // hols the jumps that have a next jump available but do not have them added yet
    std::vector<Move*> incompleteJumps;

    // for each jump that is found check if that jump has a multicapture available
    for(auto &jump: *returnMe) {
        // deleted at the end of function
        Board* boardCopy = boardState->copy();
        // push the jump to the mock board
        boardCopy->move(jump, false);

        // create a fake checker which is used to check if there is a capture available
        // deleted at the end of this function
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
            incompleteJumps.emplace_back(jump);
            for (auto &nextJump : *jumps) {
                // deleted by caller
                Move* jumpCopy = jump->copy();
                jumpCopy->setNextChainMove(nextJump);
                successorJumps->emplace_back(jumpCopy);
            }
        }
        delete boardCopy;
        delete mockChecker;
        delete jumps;
    }
    // for each jump that has a multijump available that has not been found yet
    // remove this jump from the return list
    for(auto incJump : incompleteJumps) {
        auto it = find(returnMe->begin(), returnMe->end(), incJump);
        if(it != returnMe->end()) {
            Move *jump = *it;
            returnMe->erase(it);
            delete jump;
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
            returnMe->emplace_back(LLJump);
        }
        Move *LRJump = getLRJump(checker, boardState);
        if(LRJump != nullptr) {
            returnMe->emplace_back(LRJump);
        }
        if(checker->isKing()) {
            Move *ULJump = getULJump(checker, boardState);
            if(ULJump != nullptr) {
                returnMe->emplace_back(ULJump);
            }
            Move *URJump = getURJump(checker, boardState);
            if(URJump != nullptr) {
                returnMe->emplace_back(URJump);
            }
        }
    } else {
        // do the same with player2 but in the opposite direction
        Move *ULJump = getULJump(checker, boardState);
        if(ULJump != nullptr) {
            returnMe->emplace_back(ULJump);
        }
        Move *URJump = getURJump(checker, boardState);
        if(URJump != nullptr) {
            returnMe->emplace_back(URJump);
        }
        if(checker->isKing()) {
            Move *LLJump = getLLJump(checker, boardState);
            if (LLJump != nullptr) {
                returnMe->emplace_back(LLJump);
            }
            Move *LRJump = getLRJump(checker, boardState);
            if (LRJump != nullptr) {
                returnMe->emplace_back(LRJump);
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
        vec1->emplace_back(move);
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

std::vector<Move*>* Rules::getMovesAtPos(Checker *checker, Board* boardState) {
    Color color = checker->getColor();

    auto *returnMe = new std::vector<Move *>();
    // check the possible moves for a player1 piece, else check for player2
    if (color == RED) {
        Move *LLMove = getLLMove(checker, boardState);
        if (LLMove != nullptr) {
            returnMe->emplace_back(LLMove);
        }
        Move *LRMove = getLRMove(checker, boardState);
        if (LRMove != nullptr) {
            returnMe->emplace_back(LRMove);
        }
        if (checker->isKing()) {
            Move *ULMove = getULMove(checker, boardState);
            if (ULMove != nullptr) {
                returnMe->emplace_back(ULMove);
            }
            Move *URMove = getURMove(checker, boardState);
            if (URMove != nullptr) {
                returnMe->emplace_back(URMove);
            }
        }
    } else {
        // do the same with player2 but in the opposite direction
        Move *ULMove = getULMove(checker, boardState);
        if (ULMove != nullptr) {
            returnMe->emplace_back(ULMove);
        }
        Move *URMove = getURMove(checker, boardState);
        if (URMove != nullptr) {
            returnMe->emplace_back(URMove);
        }
        if (checker->isKing()) {
            Move *LLMove = getLLMove(checker, boardState);
            if (LLMove != nullptr) {
                returnMe->emplace_back(LLMove);
            }
            Move *LRMove = getLRMove(checker, boardState);
            if (LRMove != nullptr) {
                returnMe->emplace_back(LRMove);
            }
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

bool Rules::legalDirection(Move *move, Board *boardState) {
    bool legalMove;
    if(boardState->getAt(move->getCurRow(), move->getCurCol())->isKing()) {
        legalMove = true;
    } else {
        int curRow = move->getCurRow();
        int destRow = move->getDestRow();
        if(move->getColor() == RED) {
            legalMove = (curRow - 1 == destRow);
        } else {
            legalMove = (curRow + 1 == destRow);
        }
    }
    return legalMove;
}

bool Rules::crownMe(Move *move, Board *boardState) {
    bool crowned = false;
    Checker *checker = boardState->getAt(move->getCurRow(), move->getCurCol());

    if (checker != nullptr && !checker->isKing() &&
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
    if (downRow >= 0 && rtCol <= Board::getBOARD_WIDTH()) {
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
    if (upRow <= Board::getBOARD_HEIGHT() && ltCol >= 0) {
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
    if (upRow <= Board::getBOARD_HEIGHT() && rtCol <= Board::getBOARD_WIDTH()) {
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
        // Lower left move
        Move *LLMove = new Move(row, col, downRow, ltCol,
                                -1, -1, color);
        crownMe(LLMove, boardState);
        if (validSpace(downRow, ltCol, boardState)
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
    if (downRow >= 0 && rtCol <= Board::getBOARD_WIDTH()) {
        // Lower right move
        Move* LRMove = new Move(row, col, downRow, rtCol,
                                -1, -1, color);
        crownMe(LRMove, boardState);
        if (validSpace(downRow, rtCol, boardState)
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
    int upRow = row + 1;
    int ltCol = col - 1;
    if (upRow <= Board::getBOARD_HEIGHT() && ltCol >= 0) {
        // Upper left move
        Move *ULMove = new Move(row, col, upRow, ltCol, -1, -1, color);
        crownMe(ULMove, boardState);
        if (validSpace(upRow, ltCol, boardState)
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
    int upRow = row + 1;
    int rtCol = col + 1;
    if (upRow <= Board::getBOARD_HEIGHT() && rtCol <= Board::getBOARD_WIDTH()) {
        // Upper right move
        Move *URMove = new Move(row, col, upRow, rtCol, -1, -1, color);
        crownMe(URMove, boardState);
        if (validSpace(upRow, rtCol, boardState) && legalDirection(URMove, boardState)) {
            returnMe = URMove;
        } else
            delete URMove;
    }
    return returnMe;
}