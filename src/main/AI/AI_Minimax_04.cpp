//
// Created by Luke McNamee on 2019-04-05.
//

#include "../../../include/internal/AI_Minimax_04.h"


int AI_Minimax_04::evaluateBoardState(Node *node) {
    Board *bs = node->getBoardState();
    int piecesVal = earlyGameEval(bs);

    if (bs->isEndgame()) {
        // endgame function: Sum distance of all kings, lower is better
        int kingSum = 0;
        if (this->getColor() == RED) {
            kingSum = endGameEval(bs->getRedPieces(), bs->getWhitePieces());
        } else {
            kingSum = endGameEval(bs->getWhitePieces(), bs->getRedPieces());
        }
        piecesVal += kingSum;
    }

    return piecesVal;
}

int AI_Minimax_04::earlyGameEval(Board *boardState) {
    int KING_POINT_VAL = 22;
    int MAN_POINT_VAL = 6;
    int whiteValue = 0;
    int redValue = 0;

    for (auto &c : *(boardState->getWhitePieces())) {
        if (c->isKing()) {
            whiteValue += KING_POINT_VAL;
        }
        else {
            int rowVal = c->getRow();
            whiteValue += (MAN_POINT_VAL + rowVal);
        }
    }
    for (auto &c : *(boardState->getRedPieces())) {
        if (c->isKing()) {
            redValue += KING_POINT_VAL;
        } else {
            int rowVal = abs(c->getRow() - (Board::getBOARD_HEIGHT() - 1));
            redValue += (MAN_POINT_VAL + rowVal);
        }
    }
    int returnMe = 0;
    if(this->getColor() == RED) {
        returnMe = redValue - whiteValue;
    } else {
        returnMe = whiteValue - redValue;
    }
    return returnMe;
}

int AI_Minimax_04::endGameEval(std::vector<Checker *> *myPcs,
        std::vector<Checker *> *otherPcs) {
    // return value
    int kingSum = 0;
    // indicates whether value be aggressive or defensive play
    bool isAggressor;
    std::vector<Checker *> myKings;
    std::vector<Checker *> otherKings;
    // create vectors of all king pieces by color
    for (auto &p : *myPcs) {
        if (p->isKing()) myKings.push_back(p);
    }
    for (auto &p : *otherPcs) {
        if (p->isKing()) otherKings.push_back(p);
    }
    isAggressor = myKings.size() > otherKings.size();

    for (auto &king : myKings) {
        for (auto &wk : otherKings) {
            // get the space between the two kings
            int rowDelta = abs(king->getRow() - wk->getRow()) - 1;
            int colDelta = abs(king->getCol() - wk->getCol()) - 1;
            int delta = (rowDelta > colDelta) ? rowDelta : colDelta;
                if(isAggressor) {
                    // if we are the aggressor then we want to get closer
                    kingSum += abs(6 - delta);
                } else {
                    // otherwise the distance is a direct conversion to points
                    kingSum += delta;
                }
        }
    }
    return kingSum;
}