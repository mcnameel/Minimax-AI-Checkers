//
// Created by Luke on 1/28/2019.
//

#include "Move.h"
#include "../human/Parser.h"


int Move::getCurRow() {
    return curRow;
}

int Move::getCurCol() {
    return curCol;
}

int Move::getDestRow() {
    return destRow;
}

Move::~Move() {
    if(getChainMove() != nullptr)
        delete chainMove;
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

std::string Move::toString() {
    std::string cur = std::to_string(curRow) + std::to_string(curCol) + " -> ";
    std::string cap = (capRow == -1) ? "" : std::to_string(capRow) + std::to_string(capCol) + " - > ";
    std::string dest = std::to_string(destRow) + std::to_string(destCol);
    return cur + cap + dest;
}

bool Move::operator==(const Move& m) {
    bool returnMe = false;
    if(this->getChainMove() != nullptr && m.chainMove != nullptr) {
        returnMe = (*this->getChainMove()) == (*m.chainMove);
    }
    else if(this->getChainMove() == nullptr && m.chainMove == nullptr){
        returnMe = true;
    }
    bool ret2 = curRow == m.curRow;
    bool ret3 = destRow == m.destRow && destCol == m.destCol;
    bool ret4 = capRow == m.capRow && capCol == m.capCol;
    bool ret5 = isKing == m.isKing;
    return returnMe && ret2 && ret3 && ret4 && ret5;
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

Move *Move::getChainMove() {
    return chainMove;
}

void Move::setChainMove(Move *m) {
    this->chainMove = m;
}

Move *Move::copy() {
    Move* copy = new Move(getCurRow(), getCurCol(),
            getDestRow(), getDestCol(),
            getCapRow(), getCapCol(), getColor());
    if(this->getKingMove())
        copy->setKingMove(true);
    if(this->getChainMove() != nullptr) {
        copy->setChainMove(getChainMove()->copy());
    }
    return copy;
}

bool Move::isMustChainCapture() const {
    return mustChainCapture;
}

void Move::setMustChainCapture(bool mustChainCapture) {
    Move::mustChainCapture = mustChainCapture;
}
