#include <random>

//
// Created by Luke on 2/19/2019.
//

#include <iostream>
#include <future>
#include "../../../include/internal/Node.h"
#include "../../../include/internal/Rules.h"


Node::Node() {
    leafNodeCount = 0;
    boardState = nullptr;
    move = nullptr;
    successors = nullptr;
}

Node::Node(Board *boardState, std::vector<Node *> *successors, Move *move) {
    this->boardState = boardState;
    this->move = move;
    this->successors = successors;
    this->terminal = false;
}

Node::Node(Board *boardState, Move *move) {
    this->boardState = boardState;
    this->move = move;
    this->successors = nullptr;
    this->terminal = true;
}

Node::~Node() {
    if(successors != nullptr) {
        for (auto & successor : *successors) {
            delete successor;
        }
    }
    delete successors;
    delete boardState;
    delete move;
}

Node * Node::createTree(Board *bs, int depth, Move *pMove) {
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++leafNodeCount;
        return new Node(bs, pMove);
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++leafNodeCount;
        bs->setGameOver(true);
        delete moves;
        return new Node(bs, pMove);
    }

    /* return condition 3 */
    // there are moves left to make by a both players and we have not reached
    // target depth
    // recursively call this function on each of the moves that can be made
    // return a node with successors populated
    auto *nextSuccessors = new std::vector<Node *>();
    for(auto newMove : *moves) {
        // deleted upon destruction of node
        auto *successorBS = new Board(*bs);
        // deleted at end of next recursive call or by destructor of leaf node
        successorBS->move(newMove, true);
        nextSuccessors->emplace_back(createTree(successorBS, depth - 1, newMove));
    }
    delete moves;
    return new Node(bs, nextSuccessors, pMove);
}

Node *Node::createTreeWithThreads(Board *bs, int depth, Move *pMove) {
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++leafNodeCount;
        return new Node(bs, pMove);
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++leafNodeCount;
        bs->setGameOver(true);
        delete moves;
        return new Node(bs, pMove);
    }

    /* return condition 3 */
    // there are moves left to make by a both players and we have not reached
    // target depth. For each pMove that can be made this turn.
    // On the first call, the functions will spawn a thread for
    // each recursive call which will then run in sync.
    // return a node with successors populated
    int numMoves = moves->size();
    auto *newSuccessors = new std::vector<Node *>(static_cast<unsigned int>(numMoves));
    Move *newMove = nullptr;
    for (int index = 0; index < numMoves; index++) {
        // get the pMove from the list of moves
        newMove = moves->at(static_cast<unsigned long>(index));
        // copy the board state so the pMove can be safely implemented
        auto *succBS = new Board(*bs);
        succBS->move(newMove, true);
        // start a new async thread to recursively create the tree w/o spawning
        // more threads
        //std::future<Node *> future = std::async(createTree(
        //                                        succBS, depth, nullptr));
        //newSuccessors->emplace(newSuccessors->begin() + index, future.get());
    }
    delete moves;
    return new Node(bs, newSuccessors, pMove);
}

Node *Node::appendToTree(Board *bs, int depth, Node *node) {
    /* return condition 1 */
    // traverse previous node tree until we need to create more nodes
    auto *nextSuccessors = node->getSuccessors();
    if (nextSuccessors != nullptr) {
        for (auto &child : *nextSuccessors) {
            appendToTree(child->getBoardState(), depth - 1, child);
        }
        return node;
    }

    /* return condition 2 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++leafNodeCount;
        return new Node(bs, node->getLastMove());
    }


    /* return condition 3 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++leafNodeCount;
        bs->setGameOver(true);
        delete moves;
        return new Node(bs, node->getLastMove());
    }
    else if(node->isTerminal()) {
        // else the node was previously terminal due to depth
        node->setTerminal(false);
    }

    /* return condition 4 */
    // there are moves left to make by both players and we have not reached
    // target depth
    // recursively call this function on each of the moves that can be made
    // return a node with successors populated
    nextSuccessors = new std::vector<Node *>();
    for (auto &newMove : *moves) {
        // deleted with destructor of node
        auto *succBS = new Board(*bs);
        succBS->move(newMove, true);
        nextSuccessors->emplace_back(createTree(succBS, depth - 1, newMove));
    }
    node->setSuccessors(nextSuccessors);
    delete moves;
    return node;
}

Node *Node::seekAndRemoveSuccessor(Move *findMe, Node *searchMe) {
    Node *returnMe = nullptr;
    for (auto &successor : *searchMe->getSuccessors()) {
        if(*(successor->getMove()) == *findMe) {
            returnMe = successor;
            successor = nullptr;
            break;
        }
    }
    return returnMe;
}

std::vector<Node *>* Node::getSuccessors() {
    return successors;
}

int Node::getValue() {
    return value;
}

void Node::setValue(int pValue) {
    this->value = pValue;
}

bool Node::isTerminal() {
    return terminal;
}

Move *Node::getMove() {
    return move;
}

void Node::setTerminal(bool pTerminal) {
    this->terminal = pTerminal;
}

Board *Node::getBoardState() {
    return boardState;
}

void Node::setMove(Move *pMove) {
    Node::move = pMove;
}

Move *Node::getLastMove() {
    return boardState->getLastMove();
}

void Node::setSuccessors(std::vector<Node *> *pSuccessors) {
    Node::successors = pSuccessors;
}

int Node::getLeafNodeCount() {
    return leafNodeCount;
}

bool Node::operator<(const Node &n) {
    return (this->getValue() < n.value);
}

