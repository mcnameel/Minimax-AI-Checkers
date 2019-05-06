#include <utility>

//
// Created by Luke McNamee on 2019-03-21.
//

#include <iostream>
#include <chrono>
#include "../../../include/internal/AI.h"
#include "../../../include/internal/Move.h"
#include "../../../include/internal/Board.h"

#define _timer_ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())

AI::AI(int lookAhead, Color color, std::string name, bool usePruning)
        : Player(color, std::move(name)),
          usePruning(usePruning), lookAhead(lookAhead) {}

AI::~AI() {
    delete currentTree;
    delete lastBoard;
}

Move *AI::getMove(Board *boardState) {
    // delete the old nodes and successors in the tree except for the move that
    // was taken last turn
    if(currentTree != nullptr) {
        currentTree = deleteOldNodes(*boardState, currentTree);
    }
    std::chrono::milliseconds startTimeA = _timer_;
    currentTree = makeTree(boardState);
    std::chrono::milliseconds endTimeA = _timer_;

    std::chrono::milliseconds startTimeB = _timer_;
    int bestMoveVal;
    if(usePruning) {
        bestMoveVal = minimaxAB(currentTree, lookAhead, true, MIN, MAX);
    } else {
        bestMoveVal = minimax(currentTree, lookAhead, true);
    }
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

    Node *nodeToSave = bestMoves[
            static_cast<unsigned long>(random(0,
                    static_cast<int>(bestMoves.size() - 1)))];
    // deleted by next call to this function or by this' destructor
    Move* nextMove = new Move(*nodeToSave->getMove());
    delete lastBoard;
    // deleted next time the function is called or at destructor
    lastBoard = new Board(*boardState);
    lastBoard->move(nextMove, true);

    if(currentTree == nullptr) {
        currentTree = nodeToSave;
    } else {
        currentTree = deleteOldNodes(*lastBoard, currentTree);
    }
    double genTime = ((endTimeA - startTimeA).count() / 1000.0);
    double evalTime = ((endTimeB - startTimeB).count() / 1000.0);

    //totalGenTime += genTime;
    //totalEvalTime += evalTime;
    std::cout << "Generated nodes in " << genTime << "s" << std::endl;
    std::cout << "Calculated best move in " << evalTime << "s" << std::endl;
    std::cout << "Heuristic value of best choice " << bestMoveVal << std::endl;
    //std::cout << "Evaluated avg of " << (totalNodes / totalEvalTime) << " nodes per second" << std::endl;

    return nextMove;
}

int AI::minimaxAB(Node *node, int depth, bool maximizingPlayer,
        int alpha, int beta) {
    int returnValue;
    if (depth == 0 || node->isTerminal()) {
        returnValue = evaluateBoardState(node->getBoardState());
        node->setValue(returnValue);
        return returnValue;
    }

    auto *successors = node->getSuccessors();

    // each time minimax is recursively called it returns the node from the
    // params with the best value from its successors as its value
    if (maximizingPlayer) {
        // set value to something lower than is possible in the game
        returnValue = MIN;
        // set the curBest to something to be overwritten
        node->setValue(returnValue);
        for (auto &n : *successors) {
            returnValue = max(node->getValue(),
                    minimaxAB(n, depth - 1, false, alpha, beta));
            node->setValue(returnValue);
            alpha = max(alpha, returnValue);

            // if the alpha our current value is greater than the min break
            if (beta < alpha)
                return alpha;
        }
        return returnValue;

    } else { // minimizing player
        returnValue = MAX;
        // set the curBest to something to be overwritten
        node->setValue(returnValue);
        for (auto &n : *successors) {
            // Compare the new minimax node to the last one
            returnValue = min(node->getValue(),
                    minimaxAB(n, depth - 1, true, alpha, beta));
            node->setValue(returnValue);
            beta = min(beta, returnValue);

            // if the alpha our current value is greater than the min break
            if (beta < alpha)
                return beta;
        }
        return returnValue;
    }
}

int AI::minimax(Node *node, int depth, bool maximizingPlayer) {
    int returnValue;
    if (depth == 0 || node->isTerminal()) {
        returnValue = evaluateBoardState(node->getBoardState());
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
        for (int i = successors->size() - 1; i >= 0; --i) {
            Node *n = (*successors)[i];
            returnValue = max(node->getValue(), minimax(n, depth - 1, false));
            node->setValue(returnValue);
        }
        return returnValue;

    } else { // minimizing player
        // set value to something lower than is possible in the game
        returnValue = MAX;
        // set the curBest to something to be overwritten
        node->setValue(returnValue);
        auto *successors = node->getSuccessors();
        for (auto &n : *successors) {
            // Compare the new minimax node to the last one
            returnValue = min(node->getValue(), minimax(n, depth - 1, true));
            node->setValue(returnValue);
        }
        return returnValue;
    }
}

Node *AI::makeTree(Board *bs) {
    Node factory;
    Node *newNode;
    if (currentTree == nullptr) {
        // board deleted with destructor or with the next call to
        // deleteOldNodes
        auto *newBoard = new Board(*bs);
        // pass in nullptr for move because we dont know what the head of the
        // tree is yet.
        newNode = factory.createTree(newBoard, lookAhead, nullptr);
    } else {
        // pass nullptr for the board because we already have an current board
        // from the node tree
        newNode = factory.appendToTree(nullptr, lookAhead, currentTree);
    }
    totalNodes += factory.getLeafNodeCount();
    std::cout << "Moves derivations generated: " << factory.getLeafNodeCount()
              << std::endl;
    return newNode;
}

Node *AI::deleteOldNodes(Board &boardState, Node *deleteMe) {
    Node *newTree =
            Node::seekAndRemoveSuccessor((boardState.getLastMove()), deleteMe);
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