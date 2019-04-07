//
// Created by Luke on 2/19/2019.
//

#include <iostream>
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

Node::Node() {
    this->boardState = nullptr;
    this->move = nullptr;
    this->successors = nullptr;
    this->terminal = false;
    this->value = 0;
}

Node::~Node() {
    if(successors != nullptr) {
        for (int i = 0; i < successors->size(); i++) {
            delete (*successors)[i];
        }
    }

    delete successors;
    delete boardState;
    delete move;
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
        //for (auto &newMove : *moves) {
        newMove = moves->at(static_cast<unsigned long>(index));
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        successors->push_back(createTree(succBS, depth - 1, newMove));
    }
    if(depth == orgDepth) {
        std::cout << "Moves derivations generated: " << i << std::endl;
        i = 0;
    }
    delete moves;
    return new Node(bs, successors, move);
}

void Node::createTreeWithThreads(Board *bs, int depth, Move *move, std::promise<Node *> *promisedNode) {
    static int orgDepth = depth;
    static int i = 0;
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++i;
        promisedNode->set_value(new Node(bs, move));
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++i;
        bs->setGameOver(true);
        delete moves;
        promisedNode->set_value(new Node(bs, move));
    }

    /* return condition 3 */
    // there are moves left to make by a both players and we have not reached
    // target depth
    // spawn a new thread to handle recusively call the createTree function on
    // each of the moves that can be made
    // return a node with successors populated
    std::mutex newSuccessors_mutex;
    auto *newSuccessors = new std::vector<Node*>();
    std::vector<std::thread> threads;
    Move *newMove = nullptr;
    for(int index = 0; index < moves->size(); index++) {
        // get the move from the list of moves
        newMove = moves->at(static_cast<unsigned long>(index));
        // copy the board state so the move can be safely implemented
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        // start a new async thread to resursively create the tree w/o spawning
        // more threads
        std::future<Node *> future = std::async(createTree, succBS, depth, newMove);
        newSuccessors->emplace(newSuccessors->begin() + index, future.get());
    }
    if(depth == orgDepth) {
        std::cout << "Moves derivations generated: " << i << std::endl;
        i = 0;
    }
    for (auto & delMove : *moves) {
        delete delMove;
    }
    delete moves;
    promisedNode->set_value(new Node(bs, newSuccessors, move));
}

Node *Node::createTreeWithThreads(Board *bs, int depth, Move *move) {
    static int orgDepth = depth;
    static int leafNodeCount = 0;
    static bool spawnThreads = true;
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
    // target depth
    // spawn a new thread to handle recursively call the createTree function on
    // each of the moves that can be made
    // return a node with successors populated
    std::mutex newSuccessors_mutex;
    auto *newSuccessors = new std::vector<Node*>();
    std::vector<std::thread> threads;
    Move *newMove = nullptr;
    for(int index = 0; index < moves->size(); index++) {
        // get the move from the list of moves
        newMove = moves->at(static_cast<unsigned long>(index));
        // copy the board state so the move can be safely implemented
        Board *succBS = bs->copy();
        succBS->move(newMove, true);
        // start a new async thread to resursively create the tree w/o spawning
        // more threads
        std::future<Node *> future = std::async(createTree, succBS, depth, newMove);
        newSuccessors->emplace(newSuccessors->begin() + index, future.get());
    }
    if(depth == orgDepth) {
        std::cout << "Moves derivations generated: " << leafNodeCount << std::endl;
        leafNodeCount = 0;
    }
    /*for (auto & delMove : *moves) {
        delete delMove;
    }*/
    delete moves;
    return new Node(bs, newSuccessors, move);
}

Node *Node::appendToTree(Board *bs, int depth, Node *node) {
    static int orgDepth = depth;
    static int i = 0;
    /* return condition 1 */
    // if depth is zero we have reached the target depth
    // return leaf node
    if (depth == 0 /*|| if the game is over but depth not reached make a leaf node */) {
        ++i;
        return node;
    }

    /* return condition 2 */
    // there are no moves left for a player to make, aka, they have lost
    // return leaf node
    auto *moves = Rules::getAllLegalMoves(bs);
    if (moves->empty()) {
        ++i;
        bs->setGameOver(true);
        delete moves;
        return node;
    }

    /* return condition 3 */
    // traverse previous node tree until we need to create more nodes
    auto *successors = node->getSuccessors();
    if(successors != nullptr) {
        for(auto &child : *successors) {
            appendToTree(bs, depth - 1, child);
        }
        return node;

    } else {
        /* return condition 4 */
        // there are moves left to make by a both players and we have not reached
        // target depth
        // recursively call this function on each of the moves that can be made
        // return a node with successors populated
        successors = new std::vector<Node *>();
        for (auto &newMove : *moves) {
            Board *succBS = bs->copy();
            succBS->move(newMove, true);
            successors->push_back(createTree(succBS, depth - 1, newMove));
        }
        if(depth == orgDepth) {
            std::cout << "Moves derivations generated: " << i << std::endl;
            i = 0;
        }
        delete moves;
        return new Node(bs, successors, node->getMove());
    }
}

Node *Node::seekAndRemoveSuccessor(Move *findMe, Node *searchMe) {
    for (auto &node : *searchMe->getSuccessors()) {
        if(node->getMove() == findMe) {
            auto *temp = node;
            node = nullptr;
            return node;
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
