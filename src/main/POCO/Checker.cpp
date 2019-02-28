//
// Created by Luke on 1/28/2019.
//

#include <iostream>
#include "Checker.h"

Checker::Checker(Color color, int row, int col) {
    this->COLOR = color;
    this->row = row;
    this->col = col;
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

std::string Checker::toString() {
    std::cout << getColor() << " row: " << getRow() << " | column: " << getCol() << std::endl;
    return "";
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

Checker *Checker::copy() {
    auto * c = new Checker(getColor(),getRow(), getCol());
    if(this->isKing())
        c->makeKing();
    return c;
}
