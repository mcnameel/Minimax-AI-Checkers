//
// Created by Luke on 2/8/2019.
//

#include <chrono>
#include <iostream>
#include <random>
#include "AI.h"
#include "Node.h"

int AI::minimax(Node* node, int depth, bool maximizingPlayer) {
    int returnValue;
    if (depth == 0 || node->isTerminal()) {
        returnValue = evaluateBoardState_01(node);
        node->setValue(returnValue);
        return returnValue;
    }
    // each time minimax is recursively called it returns the node from the
    // params with the best value from its successors as its value
    if (maximizingPlayer) {
        returnValue = MIN; // set value to something lower than is possible in the game
        node->setValue(returnValue); // set the curBest to something to be overwritten
        for (auto &n : *(node->getSuccessors())) {
            returnValue = max(node->getValue(), minimax(n, depth - 1, false));
            node->setValue(returnValue);
        }
        return returnValue;

    } else { // minimizing player
        returnValue = MAX;
        node->setValue(returnValue); // set the curBest to something to be overwritten
        for (auto &n : *(node->getSuccessors())) {
            // Compare the new minimax node to the last one
            returnValue = min(node->getValue(), minimax(n, depth - 1, true));
            node->setValue(returnValue);
        }
        return returnValue;
    }
}

int AI::minimaxAB(Node *node, int depth, bool maximizingPlayer, int alpha, int beta) {
    int returnValue;
    if (depth == 0 || node->isTerminal()) {
        returnValue = evaluateBoardState_03(node);
        node->setValue(returnValue);
        return returnValue;
    }
    // each time minimax is recursively called it returns the node from the
    // params with the best value from its successors as its value
    if (maximizingPlayer) {
        returnValue = MIN; // set value to something lower than is possible in the game
        node->setValue(returnValue); // set the curBest to something to be overwritten
        for (auto &n : *(node->getSuccessors())) {
            returnValue = max(node->getValue(), minimaxAB(n, depth - 1, false, alpha, beta));
            node->setValue(returnValue);
            alpha = max(alpha, returnValue);

            // if the alpha our current value is greater than the min break
            if (beta <= alpha) {
                break;
            }
        }
        return returnValue;

    } else { // minimizing player
        returnValue = MAX;
        node->setValue(returnValue); // set the curBest to something to be overwritten
        for (auto &n : *(node->getSuccessors())) {
            // Compare the new minimax node to the last one
            returnValue = min(node->getValue(), minimaxAB(n, depth - 1, true, alpha, beta));
            node->setValue(returnValue);
            beta = min(beta, returnValue);

            // if the alpha our current value is greater than the min break
            if (beta <= alpha) {
                break;
            }
        }
        return returnValue;
    }
}

int AI::evaluateBoardState_01(Node *node) {
    int KING_POINT_VAL = 3;
    int MAN_POINT_VAL = 1;
    int whiteValue = 0;
    int redValue = 0;
    Board *bs = node->getBoardState();
    for (auto &c : *(bs->getWhitePieces())) {
        if (c->isKing())
            whiteValue += KING_POINT_VAL;
        else
            whiteValue += MAN_POINT_VAL;
    }
    for (auto &c : *(bs->getRedPieces())) {
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

int AI::evaluateBoardState_02(Node *node) {
    int KING_POINT_VAL = 15;
    int MAN_POINT_VAL = 3;
    int whiteValue = 0;
    int redValue = 0;
    Board *bs = node->getBoardState();
    for (auto &c : *(bs->getWhitePieces())) {
        if (c->isKing()) {
            whiteValue += KING_POINT_VAL;
        }
        else {
            int rowVal = c->getRow();
            whiteValue += (MAN_POINT_VAL + rowVal);
        }
    }
    for (auto &c : *(bs->getRedPieces())) {
        if (c->isKing()) {
            redValue += KING_POINT_VAL;
        } else {
            int rowVal = abs(c->getRow() - (Board::BOARDHEIGHT - 1));
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

int AI::evaluateBoardState_03(Node *node) {
    int KING_POINT_VAL = 22;
    int MAN_POINT_VAL = 6;
    int whiteValue = 0;
    int redValue = 0;
    Board *bs = node->getBoardState();
    for (auto &c : *(bs->getWhitePieces())) {
        if (c->isKing()) {
            whiteValue += KING_POINT_VAL;
        }
        else {
            int rowVal = c->getRow();
            whiteValue += (MAN_POINT_VAL + rowVal);
        }
    }
    for (auto &c : *(bs->getRedPieces())) {
        if (c->isKing()) {
            redValue += KING_POINT_VAL;
        } else {
            int rowVal = abs(c->getRow() - (Board::BOARDHEIGHT - 1));
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

int AI::maxNode(Node *n1, Node *n2) {
    int returnMe = n1->getValue();
    if(n1->getValue() < n2->getValue())
        returnMe = n2->getValue();
    return returnMe;
}

int AI::minNode(Node *n1, Node *n2) {
    int returnMe = n1->getValue();
    if(n1->getValue() > n2->getValue())
        returnMe = n2->getValue();
    return returnMe;
}

int AI::max(int val1, int val2) {
    int returnMe = val1;
    if(val1 < val2)
        returnMe = val2;
    return returnMe;
}

int AI::min(int val1, int val2) {
    int returnMe = val1;
    if(val1 > val2)
        returnMe = val2;
    return returnMe;
}

Node *AI::makeTree(Board *bs) {
    return Node::createTree(bs->copy(), lookAhead, nullptr);
}

Move *AI::getMove(Board *boardState) {
    std::cout << "making tree" << std::endl;
    Node* nextMoveTree = makeTree(boardState);
    int bestMoveVal = minimaxAB(nextMoveTree, lookAhead, true, MIN, MAX);
    std::cout << "calculated best move, valued at " << bestMoveVal << std::endl;

    Move* nextMove = nullptr;

    if(nextMoveTree->getSuccessors()->empty()) {
        boardState->setGameOver(true);
    }

    auto *bestMoves = new std::vector<Move*>();
    for(auto &node : *nextMoveTree->getSuccessors()) {
        if(node->getValue() == bestMoveVal) {
            bestMoves->push_back(node->getMove());
        }
    }
    nextMove = bestMoves->at(static_cast<unsigned long>(random(0, static_cast<int>(bestMoves->size() - 1))))->copy();
    bestMoves->clear();
    delete nextMoveTree;
    delete bestMoves;
    return nextMove;
}

AI::AI(int lookAhead, Color color) : Player(color) {
    this->lookAhead = lookAhead;
}

int AI::random(int low, int high) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random(
            static_cast<unsigned int>(low), static_cast<unsigned int>(high)
            );
    return random(rng);
}


