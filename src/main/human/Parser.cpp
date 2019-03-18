//
// Created by Luke on 1/28/2019.
//

#include "Parser.h"
#include <iostream>
#include <string>
#include <regex>

Parser::Parser(Color color) : Player(color) {
}

bool Parser::validateInput(std::string in) {
    return (std::regex_match(in, std::regex("([a-h][0-7])(->[a-h][0-7])*")));
}

Move *Parser::convertInput(std::string in) {
    int offset = 4;
    int numOfMoves = (in.size() - 2) / offset;
    int indexRow1 = 1;
    int indexCol1 = 0;
    int indexRow2 = 5;
    int indexCol2 = 4;

    Move* returnMe;
    Move* lastMove;
    for(int i = 0; i < numOfMoves; i++) {
        Move* temp = new Move(in.at(indexRow1 + (offset * i)) - ROW_SHIFT,
                              in.at(indexCol1 + (offset * i)) - COLUMN_SHIFT,
                              in.at(indexRow2 + (offset * i)) - ROW_SHIFT,
                              in.at(indexCol2 + (offset * i)) - COLUMN_SHIFT,
                              playerColor);
        if(i == 0) {
            returnMe = lastMove = temp;
        }
        else {
            lastMove->setChainMove(temp);
            lastMove = temp;
        }
    }
    return returnMe;
}

Move *Parser::getMove(Board *boardState) {
    std::string in = "";
    std::cout << "\nEnter the current then destination square separated "
              << "by a \'->\' \n(aka a2->b3): ";

    std::cin >> in;
    while(!validateInput(in)) {
        std::cout << "Please enter only values matching the regex "
                  << "[a-h][0-7]->[a-h][0-7]: ";
        std::cin >> in;
    }
    return convertInput(in);
};