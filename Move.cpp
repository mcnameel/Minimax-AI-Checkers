//
// Created by Luke on 1/28/2019.
//

#include "Move.h"
#include "Parser.h"


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

char Move::getColor() {
    return color;
}

int Move::getCapRow() {
    return capRow;
}

int Move::getCapCol() {
    return capCol;
}

Move::Move(int curRow, int curCol, int destRow, int destCol, char color) {
    this->curRow = curRow;
    this->curCol = curCol;
    this->destRow = destRow;
    this->destCol = destCol;
    this->color = color;
}

Move::Move(int curRow, int curCol, int destRow, int destCol, int capRow,
        int capCol, char color) {
    this->curRow = curRow;
    this->curCol = curCol;
    this->destRow = destRow;
    this->destCol = destCol;
    this->capRow = capRow;
    this->capCol = capCol;
    this->color = color;
}

std::string Move::toString() {
    return std::to_string(curRow) + std::to_string(curCol) + " -> "
    +      std::to_string(capRow) + std::to_string(capCol) + " - > "
    +      std::to_string(destRow) + std::to_string(destCol);
}

bool Move::operator==(const Move& m) {
    return (curRow == m.curRow &&
        curCol == m.capCol &&
        destRow == m.destRow &&
        destCol == m.destCol &&
        capRow == m.capRow &&
        capCol == m.capCol);
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
