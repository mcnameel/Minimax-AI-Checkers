//
// Created by Luke on 2/19/2019.
//

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
    // if depth is zero we have reached the target depth
    if (depth == 0) {
        return new Node(bs, move); // return leaf node
    }


    auto *successors = new std::vector<Node *>();
    auto *moves = Rules::getAllLegalMoves(bs);
    for (auto &newMove : *moves) {
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        successors->push_back(createTree(succBS, depth - 1, newMove));
    }
    return new Node(bs, successors, move);
}

Node::~Node() {
    successors->clear();
    delete successors, boardState;
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
