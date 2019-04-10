//
// Created by Luke McNamee on 2019-03-21.
//

#include <iostream>
#include "../../../include/internal/AI.h"
#include "../../../include/internal/Move.h"
#include "../../../include/internal/Board.h"
#define _timer_ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
Move *AI::getMove(Board *boardState) {
    // delete the old nodes and successors in the tree except for the move that
    // was taken last turn
    if(currentTree != nullptr) {
        currentTree = deleteOldNodes(boardState, currentTree);
    }
    std::chrono::milliseconds startTimeA = _timer_;
    currentTree = makeTree(boardState);
    std::chrono::milliseconds endTimeA = _timer_;

    std::chrono::milliseconds startTimeB = _timer_;
    int bestMoveVal = minimaxAB(currentTree, lookAhead, true, MIN, MAX);
    std::chrono::milliseconds endTimeB = _timer_;

    if(currentTree->getSuccessors()->empty()) {
        boardState->setGameOver(true);
    }

    std::vector<Node *> bestMoves;
    for(auto &node : *currentTree->getSuccessors()) {
        if(node->getValue() == bestMoveVal) {
            bestMoves.push_back(node);
        }
    }

    Node *nodeToSave = bestMoves[static_cast<unsigned long>(random(0,
                                 static_cast<int>(bestMoves.size() - 1)))];
    Move* nextMove = nodeToSave->getMove()->copy();

    delete lastBoard;
    lastBoard = boardState->copy();
    lastBoard->move(nextMove, true);

    if(currentTree == nullptr) {
        currentTree = nodeToSave;
    } else {
        currentTree = deleteOldNodes(lastBoard, currentTree);
    }
    std::cout << "Generated nodes in " << ((endTimeA - startTimeA).count() / 1000.0) << "s" << std::endl;
    std::cout <<"Calculated best move in " << ((endTimeB - startTimeB).count() / 1000.0) << "s" << std::endl;
    std::cout << "Heuristic value of best choice " << bestMoveVal << std::endl;

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
        auto *successors = node->getSuccessors();
        std::sort(successors->begin(), successors->end());
        for (int i = successors->size() - 1; i >= 0; --i) {
            Node *n = (*successors)[i];
            returnValue = max(node->getValue(),
                    minimaxAB(n, depth - 1, false, alpha, beta));
            node->setValue(returnValue);
            alpha = max(alpha, returnValue);

            // if the alpha our current value is greater than the min break
            if (beta <= alpha) {
                //break;
            }
        }
        return returnValue;

    } else { // minimizing player
        returnValue = MAX;
        // set the curBest to something to be overwritten
        node->setValue(returnValue);
        auto *successors = node->getSuccessors();
        std::sort(successors->begin(), successors->end());
        for (auto &n : *successors) {
            // Compare the new minimax node to the last one
            returnValue = min(node->getValue(),
                    minimaxAB(n, depth - 1, true, alpha, beta));
            node->setValue(returnValue);
            beta = min(beta, returnValue);

            // if the alpha our current value is greater than the min break
            if (beta <= alpha) {
                // break;
            }
        }
        return returnValue;
    }
}

Node *AI::makeTree(Board *bs) {
    int *leafNodeCount = new int();
    Node *newNode;
    if (currentTree == nullptr) {
        newNode = Node::createTree(bs->copy(), lookAhead, nullptr, leafNodeCount);
    } else {
        newNode = Node::appendToTree(bs->copy(), lookAhead, currentTree, leafNodeCount);
    }
    std::cout << "Moves derivations generated: " << *leafNodeCount << std::endl;
    delete leafNodeCount;
    return newNode;
}

Node *AI::deleteOldNodes(Board *boardState, Node *deleteMe) {
    Node *newTree = Node::seekAndRemoveSuccessor(boardState->getLastMove(), deleteMe);
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

AI::~AI() {
    delete currentTree;
    delete lastBoard;
}
