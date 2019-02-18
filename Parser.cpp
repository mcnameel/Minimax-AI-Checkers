//
// Created by Luke on 1/28/2019.
//

#include "Parser.h"
#include <iostream>
#include <string>

Parser::Parser(char color) {
    this->color = color;
}

bool Parser::validateInput(std::string in) {
    return (in.size() == 6 && // Check the size
        // check that the rows are between 0 and 7
        (int) in.at(1) >= ROW_SHIFT && (int) in.at(1) <= ROW_SHIFT + 7 &&
        (int) in.at(5) >= ROW_SHIFT && (int) in.at(5) <= ROW_SHIFT + 7 &&
        // check that the columns are between a and h
        (int) in.at(0) >= COLUMN_SHIFT && (int) in.at(1) <= COLUMN_SHIFT + 7 &&
        (int) in.at(4) >= COLUMN_SHIFT && (int) in.at(5) <= COLUMN_SHIFT + 7);
}

Move *Parser::convertInput(std::string in) {
    return new Move((int) in.at(1) - ROW_SHIFT,
             (int) in.at(0) - COLUMN_SHIFT,
             (int) in.at(5) - ROW_SHIFT,
             (int) in.at(4) - COLUMN_SHIFT,
             color);
}

int Parser::translateMove(char a) {
    int returnMe;
    switch (a) {
        case 'a':
            returnMe = 0;
            break;
        case 'b':
            returnMe = 1;
            break;
        case 'c':
            returnMe = 2;
            break;
        case 'd':
            returnMe = 3;
            break;
        case 'e':
            returnMe = 4;
            break;
        case 'f':
            returnMe = 5;
            break;
        case 'g':
            returnMe = 6;
            break;
        case 'h':
            returnMe = 7;
            break;
        default:
            break;
    }
    return returnMe;
}

char Parser::translateBack(int i) {
    int returnMe;
    switch (i) {
        case 0:
            returnMe = 'a';
            break;
        case 1:
            returnMe = 'b';
            break;
        case 2:
            returnMe = 'c';
            break;
        case 3:
            returnMe = 'd';
            break;
        case 4:
            returnMe = 'e';
            break;
        case 5:
            returnMe = 'f';
            break;
        case 6:
            returnMe = 'g';
            break;
        case 7:
            returnMe = 'h';
            break;
        default:
            break;
    }
    return returnMe;
}
