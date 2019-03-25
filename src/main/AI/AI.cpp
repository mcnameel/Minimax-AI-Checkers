//
// Created by Luke McNamee on 2019-03-21.
//

#include <iostream>
#include "AI.h"
#include "../POCO/Move.h"
#include "../Board.h"

Move *AI::getMove(Board *boardState) {
    // delete the old nodes and successors in the tree except for the move that
    // was taken last turn
    if(currentTree != nullptr) {
        currentTree = deleteOldNodes(lastBoard, currentTree);
        currentTree = deleteOldNodes(boardState, currentTree);
    }
    std::cout << "Making tree" << std::endl;
    Node* nextMoveTree = makeTree(boardState);
    int bestMoveVal = minimaxAB(nextMoveTree, lookAhead, true, MIN, MAX);
    std::cout << "Calculated best move valued at " << bestMoveVal << std::endl;

    Move* nextMove = nullptr;
    if(nextMoveTree->getSuccessors()->empty()) {
        boardState->setGameOver(true);
    }

    auto *bestMoves = new std::vector<Node*>();
    for(auto &node : *nextMoveTree->getSuccessors()) {
        if(node->getValue() == bestMoveVal) {
            bestMoves->push_back(node);
        }
    }

    Node *nodeToSave = bestMoves->at(static_cast<unsigned long>(
            random(0, static_cast<int>(bestMoves->size() - 1))));
    nextMove = nodeToSave->getMove()->copy();

    lastBoard = boardState->copy();
    lastBoard->move(nextMove, true, true);

    bestMoves->clear();
    delete bestMoves;
    return nextMove;
}

AI::AI(int lookAhead, Color color) : Player(color) {
    this->lookAhead = lookAhead;
}

int AI::minimaxAB(Node *node, int depth, bool maximizingPlayer,
        int alpha, int beta) {
    int returnValue;
    if (depth == 0 || node->isTerminal()) {
        returnValue = evaluateBoardState(node);
        node->setValue(returnValue);
        return returnValue;
    }
    // each time minimax is recursively called it returns the node from the
    // params with the best value from its successors as its value
    if (maximizingPlayer) {
        // set value to something lower than is possible in the game
        returnValue = MIN;
        // set the curBest to something to be overwritten
        node->setValue(returnValue);
        for (auto &n : *(node->getSuccessors())) {
            returnValue = max(node->getValue(),
                    minimaxAB(n, depth - 1, false, alpha, beta));
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
        // set the curBest to something to be overwritten
        node->setValue(returnValue);
        for (auto &n : *(node->getSuccessors())) {
            // Compare the new minimax node to the last one
            returnValue = min(node->getValue(),
                    minimaxAB(n, depth - 1, true, alpha, beta));
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

Node *AI::makeTree(Board *bs) {
    if (currentTree == nullptr) {
        return Node::createTree(bs->copy(), lookAhead, nullptr);
    } else {
        return Node::appendToTree(bs->copy(), lookAhead, currentTree);
    }
}

Node *AI::deleteOldNodes(Board *boardState, Node *deleteMe) {
    Node *newTree = Node::seekAndRemoveSuccessor(
            boardState->getLastMove(), deleteMe);
    delete deleteMe;
    return newTree;
}

int AI::random(int low, int high) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random(
            static_cast<unsigned int>(low), static_cast<unsigned int>(high));
    return random(rng);
}

int AI::min(int val1, int val2) {
    int returnMe = val1;
    if(val1 > val2)
        returnMe = val2;
    return returnMe;
}

int AI::max(int val1, int val2) {
    int returnMe = val1;
    if(val1 < val2)
        returnMe = val2;
    return returnMe;
}
