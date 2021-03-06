//
// Created by Luke on 1/28/2019.
//

#include "../../../include/internal/Move.h"
#include "../../../include/internal/Parser.h"

Move::Move(int curRow, int curCol, int destRow, int destCol, Color color) {
    this->curRow = curRow;
    this->curCol = curCol;
    this->destRow = destRow;
    this->destCol = destCol;
    this->color = color;
}

Move::Move(int curRow, int curCol, int destRow, int destCol, int capRow,
           int capCol, Color color) {
    this->curRow = curRow;
    this->curCol = curCol;
    this->destRow = destRow;
    this->destCol = destCol;
    this->capRow = capRow;
    this->capCol = capCol;
    this->color = color;
}

Move::Move(const Move &move) : curRow(move.curRow), curCol(move.curCol),
            destRow(move.destRow), destCol(move.destCol), capRow(move.capRow),
            capCol(move.capCol), color(move.color), isKing(move.isKing),
            chainMove(move.chainMove) {
    if(move.nextChainMove != nullptr) {
        // deleted by this' destructor
        nextChainMove = new Move(*move.nextChainMove);
    }
}

Move::~Move() {
    if(getNextChainMove() != nullptr)
        delete nextChainMove;
}

Move *Move::copy() {
    Move* copy = new Move(getCurRow(), getCurCol(),
                          getDestRow(), getDestCol(),
                          getCapRow(), getCapCol(), getColor());
    if(this->getKingMove())
        copy->setKingMove(true);
    if(this->isChainMove()) {
        copy->setIsChainMove(true);
    }
    if(this->getNextChainMove() != nullptr) {
        // deleted by destructor
        copy->setNextChainMove(this->getNextChainMove()->copy());
    }
    return copy;
}

const std::string Move::toString() {
    std::string cur = std::to_string(curRow) + std::to_string(curCol) + " -> ";
    std::string cap = (capRow == -1) ? "" : std::to_string(capRow) + std::to_string(capCol) + " - > ";
    std::string dest = std::to_string(destRow) + std::to_string(destCol);
    std::string otherInfo = (isKing? " King Move " : "") + (chainMove ? getNextChainMove()->toString() : "");
    return cur + cap + dest + otherInfo;
}

bool Move::operator==(const Move& m) {
    bool returnMe1 = curRow == m.curRow && curCol == m.curCol
                     && destRow == m.destRow && destCol == m.destCol
                     && capRow == m.capRow && capCol == m.capCol
                     && chainMove == m.chainMove
                     && isKing == m.isKing;
    bool returnMe = false;
    if(this->getNextChainMove() != nullptr && m.nextChainMove != nullptr) {
        returnMe = (*this->getNextChainMove()) == (*m.nextChainMove);
    } else if(this->getNextChainMove() == nullptr && m.nextChainMove == nullptr){
        returnMe = true;
    }
    return returnMe && returnMe1;
}

int Move::getCurRow() {
    return curRow;
}

int Move::getCurCol() {
    return curCol;
}

int Move::getDestRow() {
    return destRow;
}

int Move::getDestCol() {
    return destCol;
}

Color Move::getColor() {
    return color;
}

int Move::getCapRow() {
    return capRow;
}

int Move::getCapCol() {
    return capCol;
}

void Move::setCapSpace(int row, int col) {
    this->capRow = row;
    this->capCol = col;
}

void Move::setKingMove(bool isKing) {
    this->isKing = isKing;
}

bool Move::getKingMove() {
    return isKing;
}

Move *Move::getNextChainMove() {
    return nextChainMove;
}

void Move::setNextChainMove(Move *m) {
    m->setIsChainMove(true);
    this->nextChainMove = m;
}

bool Move::isChainMove() {
    return chainMove;
}

void Move::setIsChainMove(bool isChainMove) {
    this->chainMove = isChainMove;
}
