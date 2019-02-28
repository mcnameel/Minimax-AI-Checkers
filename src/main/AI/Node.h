//
// Created by Luke on 2/19/2019.
//

#ifndef CHECKERS_01_NODE_H
#define CHECKERS_01_NODE_H

#include<vector>
#include "../POCO/Move.h"
#include "../Board.h"
#include "MinimaxTree.h"

class Node {
private:
    int value;
    bool terminal = false;
    Node* predecessor;
    std::vector<Node*>* successors;
    Board* boardState;
public:
    void setMove(Move *move);

private:
    Move* move;
public:
    std::vector<Node*>* getSuccessors();
    Node* getPredecessor();
    int getValue();
    void setValue(int value);
    void setPredecessor(Node* pred);
    void setSuccessors(std::vector<Node*>* succ);
    bool isTerminal();
    void setTerminal(bool terminal);
    void setHead(bool head);
    bool isHead();
    Move* getMove();
    Move* getLastMove();
    Board* getBoardState();

    /**
     * Constructs a non-leaf node
     * @param boardState the boardstate after the move has been completed
     * @param successors the successors of this node
     */
    Node(Board *boardState, std::vector<Node *> *successors, Move *move);


    /**
     * Constructs a leaf/terminal node
     * @param move the move that lead to this boardstate
     * @param boardState the boardstate after the move has been completed
     */
    Node(Board *boardState, Move *move);
    Node(int value);
    ~Node();

    static Node *createTree(Board *bs, int depth, Move *move);
};


#endif //CHECKERS_01_NODE_H
