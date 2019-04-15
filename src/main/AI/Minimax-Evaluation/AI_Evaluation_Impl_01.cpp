//
// Created by Luke on 2/8/2019.
//

#include <chrono>
#include <iostream>
#include <random>
#include "../../../../include/internal/AI_Evaluation_Impl_01.h"
#include "../../../../include/internal/Node.h"

int AI_Minimax_01::evaluateBoardState(Board *boardState) {
    int KING_POINT_VAL = 3;
    int MAN_POINT_VAL = 1;
    int whiteValue = 0;
    int redValue = 0;
    for (auto &c : *(boardState->getWhitePieces())) {
        if (c->isKing())
            whiteValue += KING_POINT_VAL;
        else
            whiteValue += MAN_POINT_VAL;
    }
    for (auto &c : *(boardState->getRedPieces())) {
        if (c->isKing())
            redValue += KING_POINT_VAL;
        else
            redValue += MAN_POINT_VAL;
    }
    int returnMe = 0;
    if(this->getColor() == RED) {
        returnMe = redValue - whiteValue;
    } else {
        returnMe = whiteValue - redValue;
    }
    return returnMe;
}