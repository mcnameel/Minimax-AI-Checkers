//
// Created by Luke on 1/28/2019.
//

#include <iostream>
#include "../../../include/internal/Checker.h"

Checker::Checker(Color color, int row, int col) {
    this->COLOR = color;
    this->row = row;
    this->col = col;
}

std::string Checker::toString() {
    std::cout << getColor() << " row: " << getRow() << " | column: " << getCol() << std::endl;
    return "";
}

bool Checker::operator==(const Checker &c) {
    return (this->getColor() == c.COLOR
            && this->getCol() == c.col
            && this->getRow() == c.row
            && this->isKing() == c.king);
}

Color Checker::getColor() {
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

char Checker::getColorChar() {
    char returnMe;
    if(getColor() == RED){
        if(isKing())
            returnMe = 'R';
        else
            returnMe = 'r';
    } else {
        if(isKing())
            returnMe = 'W';
        else
            returnMe = 'w';
    }
    return returnMe;
}
