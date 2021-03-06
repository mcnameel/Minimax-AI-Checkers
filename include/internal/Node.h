//
// Created by Luke on 2/19/2019.
//

#ifndef MINIMAX_AI_CHECKERS_NODE_H
#define MINIMAX_AI_CHECKERS_NODE_H

#include<vector>
#include "Move.h"
#include "Board.h"

/**
 * a node of the move tree which is used to represent all of the possible move
 * derivations possible
 */
class Node {

private:
    // the value of the node
    int value;
    // indicates this is a leaf
    bool terminal;
    // the move which this node represents
    Move *move;
    // the successors of this node
    std::vector<Node *> *successors;
    // the board state of this node
    Board *boardState;
    // the counter for the number of leaf nodes generated
    int leafNodeCount;

public:
    /* constructors and destructor */
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

    /**
     * constructs a blank node to use to call the createTree method
     */
    Node();

    /**
     * destroys the node and deletes its fields
     */
    ~Node();

    /* methods */
    /**
     * Traverses the successors of a node and returns the node that holds the
     * move provided in the parameter
     * @param findMe the move to find
     * @param searchMe the node to search
     * @return the node contains findMe
     */
    static Node *seekAndRemoveSuccessor(Move *findMe, Node *searchMe);

    /**
     * creates a tree from the board and move provided to the depth requested
     * @param bs the current board
     * @param depth desired depth
     * @param pMove the move to start from
     * @return the head of the node tree
     */
    Node *createTree(Board *bs, int depth, Move *pMove);

    /**
     * creates a tree from the board and move provided to the depth requested
     * @param bs the current board
     * @param depth desired depth
     * @param pMove the move to start from
     * @return the head of the node tree
     */
    Node *createTreeWithThreads(Board *bs, int depth, Move *pMove);

    /**
     * traverses an existing tree to append nodes the the end of that tree
     * until it is the desired depth
     * @param bs the current board
     * @param depth desired depth
     * @param node the node to start from
     * @return the head of the node tree
     */
    Node *appendToTree(Board *bs, int depth, Node *node);

    /**
     * a custom exception which triggers if the node is not found in the
     * seekAndRemoveSuccessor function
     */
    struct NodeNotFoundException : public std::exception {
        const char *what() const noexcept override {
            return "The node containing the move provided was not found within"
                   "the successors of the node provided";
        }
    };

    /* operators */
    /**
     * compares the nodes by value field of the node
     */
    bool operator<(const Node &n);

    /* accessors and mutators */
    std::vector<Node *> *getSuccessors();

    void setMove(Move *pMove);

    int getValue();

    void setValue(int pValue);

    bool isTerminal();

    void setTerminal(bool pTerminal);

    Move *getMove();

    Move *getLastMove();

    Board *getBoardState();

    void setSuccessors(std::vector<Node *> *pSuccessors);

    int getLeafNodeCount();

};

#endif //MINIMAX_AI_CHECKERS_NODE_H
