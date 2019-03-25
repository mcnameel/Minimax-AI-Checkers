//
// Created by Luke McNamee on 2019-03-21.
//

#include "AI_Minimax_02.h"

int AI_Minimax_02::evaluateBoardState(Node *node) {
    int KING_POINT_VAL = 15;
    int MAN_POINT_VAL = 3;
    int whiteValue = 0;
    int redValue = 0;
    Board *bs = node->getBoardState();
    for (auto &c : *(bs->getWhitePieces())) {
        if (c->isKing()) {
            whiteValue += KING_POINT_VAL;
        } else {
            int rowVal = c->getRow();
            whiteValue += (MAN_POINT_VAL + rowVal);
        }
    }
    for (auto &c : *(bs->getRedPieces())) {
        if (c->isKing()) {
            redValue += KING_POINT_VAL;
        } else {
            int rowVal = abs(c->getRow() - (Board::getBOARDHEIGHT() - 1));
            redValue += (MAN_POINT_VAL + rowVal);
        }
    }
    int returnMe = 0;
    if (this->getColor() == RED) {
        returnMe = redValue - whiteValue;
    } else {
        returnMe = whiteValue - redValue;
    }
    return returnMe;
}
