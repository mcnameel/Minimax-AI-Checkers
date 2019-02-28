//
// Created by Luke on 2/8/2019.
//

#include <chrono>
#include <iostream>
#include <random>
#include "AI.h"
#include "Node.h"

Node* AI::minimax(Node* node, int depth, bool maximizingPlayer) {
    if (depth == 0 || node->isTerminal()) {
        int value = evaluateBoardState(node);
        node->setValue(value);
        return node;
    }
    // each time minimax is recursively called it returns the node from the
    // params with the best value from its successors as its value
    if (maximizingPlayer) {
        int value = -200; // set value to something lower than is possible in the game
        node->setValue(value); // set the curBest to something to be overwritten
        for (auto &n : *(node->getSuccessors())) {
            node->setValue(max(node, minimax(n, depth - 1, false)));
        }
    } else { // minimizing player
        int value = 200;
        node->setValue(value); // set the curBest to something to be overwritten
        for (auto &n : *(node->getSuccessors())) {
            // Compare the new minimax node to the last one
            node->setValue(min(node, minimax(n, depth - 1, true)));
        }
    }
    return node;
}

int AI::evaluateBoardState(Node *node) {
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
    if(node->getLastMove()->getColor() == RED) {
        returnMe = redValue - whiteValue;
    } else {
        returnMe = whiteValue - redValue;
    }
    return returnMe;
}

int AI::max(Node *n1, Node *n2) {
    int returnMe = n1->getValue();
    if(n1->getValue() < n2->getValue())
        returnMe = n2->getValue();
    return returnMe;
}

int AI::min(Node *n1, Node *n2) {
    int returnMe = n1->getValue();
    if(n1->getValue() > n2->getValue())
        returnMe = n2->getValue();
    return returnMe;
}

Node *AI::makeTree(Board *bs) {
    return Node::createTree(bs, lookAhead, nullptr);
}

Move *AI::getMove(Board *boardState) {
    Node* nextMoveTree = makeTree(boardState);
    nextMoveTree = minimax(nextMoveTree, lookAhead, true);
    Move* nextMove;

    for(auto &node : *nextMoveTree->getSuccessors()) {
        if(node->getValue() == nextMoveTree->getValue())
            nextMove = node->getMove()->copy();
    }
    delete nextMoveTree;
    return nextMove;
}

AI::AI(int lookAhead) {
    this->lookAhead = lookAhead;
}

int AI::random(int low, int high) {
    std::default_random_engine generator(time(nullptr));
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}


