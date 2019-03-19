//
// Created by Luke on 2/19/2019.
//

#include <iostream>
#include "Node.h"
#include "../Rules.h"

std::vector<Node *>* Node::getSuccessors() {
    return successors;
}

Node *Node::getPredecessor() {
    return predecessor;
}

int Node::getValue() {
    return value;
}

void Node::setValue(int value) {
    this->value = value;
}

bool Node::isTerminal() {
    return terminal;
}

Node::Node(Board *boardState, std::vector<Node *> *successors, Move *move) {
    this->boardState = boardState;
    this->successors = successors;
    this->move = move;
    this->terminal = false;
}

Node::Node(Board *boardState, Move *move) {
    this->boardState = boardState;
    this->terminal = true;
    this->move = move;
}

Node * Node::createTree(Board *bs, int depth, Move *move) {
    static int orgDepth = depth;
    static int i = 0;
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++i;
        return new Node(bs, move);
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++i;
        bs->setGameOver(true);
        return new Node(bs, move);
    }

    /* return condition 3 */
    // there are moves left to make by a both players and we have not reached
    // target depth
    // recursively call this function on each of the moves that can be made
    // return a node with successors populated
    auto *successors = new std::vector<Node *>();
    for (auto &newMove : *moves) {
        Board *succBS = bs->copy();
        succBS->move(newMove, true, true);
        successors->push_back(createTree(succBS, depth - 1, newMove));
    }
    if(depth == orgDepth) {
        std::cout << "Moves derivations generated: " << i << std::endl;
        i = 0;
    }
    return new Node(bs, successors, move);
}

Node::~Node() {
    successors->clear();
    delete successors, boardState, move;
}

Move *Node::getMove() {
    return move;
}

void Node::setTerminal(bool terminal) {
    this->terminal = terminal;
}

Board *Node::getBoardState() {
    return boardState;
}

void Node::setMove(Move *move) {
    Node::move = move;
}

Node::Node(int value) {
    this->value = value;
}

Move *Node::getLastMove() {
    return boardState->getLastMove();
}
