//
// Created by Luke on 2/19/2019.
//

#include <iostream>
#include <future>
#include "../../../include/internal/Node.h"
#include "../../../include/internal/Rules.h"

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

Node * Node::createTree(Board *bs, int depth, Move *move, int *leafNodeCount) {
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++(*leafNodeCount);
        return new Node(bs, move);
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++(*leafNodeCount);
        bs->setGameOver(true);
        delete moves;
        return new Node(bs, move);
    }

    /* return condition 3 */
    // there are moves left to make by a both players and we have not reached
    // target depth
    // recursively call this function on each of the moves that can be made
    // return a node with successors populated
    auto *successors = new std::vector<Node *>();
    Move *newMove = nullptr;
    for(int index = 0; index < moves->size(); index++) {
        newMove = moves->at(static_cast<unsigned long>(index));
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        successors->push_back(createTree(succBS, depth - 1, newMove, leafNodeCount));
    }
    delete moves;
    return new Node(bs, successors, move);
}

Node *Node::createTreeWithThreads(Board *bs, int depth, Move *move) {
    static int orgDepth = depth;
    static int leafNodeCount = 0;
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++leafNodeCount;
        return new Node(bs, move);
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++leafNodeCount;
        bs->setGameOver(true);
        delete moves;
        return new Node(bs, move);
    }

    /* return condition 3 */
    // there are moves left to make by a both players and we have not reached
    // target depth. For each move that can be made this turn.
    // On the first call, the functions will spawn a thread for
    // each recursive call which will then run in sync.
    // return a node with successors populated
    int numMoves = moves->size();
    auto *newSuccessors = new std::vector<Node *>(numMoves);
    Move *newMove = nullptr;
    for (int index = 0; index < numMoves; index++) {
        // get the move from the list of moves
        newMove = moves->at(static_cast<unsigned long>(index));
        // copy the board state so the move can be safely implemented
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        // start a new async thread to recursively create the tree w/o spawning
        // more threads
        int *counter = new int();
        long long *counter1 = new long long();
        long long *counter2 = new long long();
        std::future<Node *> future = std::async(createTree,
                                                succBS, depth, nullptr, counter);
        newSuccessors->emplace(newSuccessors->begin() + index, future.get());
    }
    // print out the number leaf nodes reached
    if (depth == orgDepth) {
        std::cout << "Moves derivations generated: " << leafNodeCount
                  << std::endl;
        leafNodeCount = 0;
    }
    delete moves;
    return new Node(bs, newSuccessors, move);
}

Node *Node::appendToTree(Board *bs, int depth, Node *node,int *leafNodeCount) {

    /* return condition 1 */
    // traverse previous node tree until we need to create more nodes
    auto *successors = node->getSuccessors();
    if (successors != nullptr) {
        for (auto &child : *successors) {
            appendToTree(child->boardState, depth - 1, child, leafNodeCount);
        }
        return node;
    }

    /* return condition 2 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++(*leafNodeCount);
        return new Node(bs, node->getLastMove());
    }


    /* return condition 3 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++(*leafNodeCount);
        bs->setGameOver(true);
        delete moves;
        return new Node(bs, node->getLastMove());
    }
    else if(node->isTerminal()) {
        // else the node was previously terminal due to depth
        node->setTerminal(false);
    }

    /* return condition 4 */
    // there are moves left to make by a both players and we have not reached
    // target depth
    // recursively call this function on each of the moves that can be made
    // return a node with successors populated
    successors = new std::vector<Node *>();
    for (auto &newMove : *moves) {
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        successors->push_back(createTree(succBS, depth - 1, newMove, leafNodeCount));
    }
    node->setSuccessors(successors);
    delete moves;
    return node;
}

Node *Node::seekAndRemoveSuccessor(Move *findMe, Node *searchMe) {
    for (auto & successor : *searchMe->getSuccessors()) {
        if(*(successor->getMove()) == *findMe) {
            auto *temp = successor;
            successor = nullptr;
            return temp;
        }
    }
    throw NodeNotFoundException();
}

std::vector<Node *>* Node::getSuccessors() {
    return successors;
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

Move *Node::getLastMove() {
    return boardState->getLastMove();
}

void Node::setSuccessors(std::vector<Node *> *successors) {
    Node::successors = successors;
}

bool Node::operator<(const Node &n) {
    return (this->getValue() < n.value);
}
