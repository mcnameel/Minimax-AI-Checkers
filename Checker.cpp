//
// Created by Luke on 1/28/2019.
//

#include "Checker.h"

Checker::Checker(char color, int row, int col) {
    this->COLOR = color;
    this->row = row;
    this->col = col;
}

char Checker::getColor() {
    return COLOR;
}

bool Checker::isKing() {
    return king;
}

void Checker::makeKing() {
    king = true;
}

int Checker::getRow() {
    return row;
}

void Checker::setRow(int r) {
    this->row = r;
}

int Checker::getCol() {
    return col;
}

void Checker::setCol(int c) {
    this->col = c;
}
