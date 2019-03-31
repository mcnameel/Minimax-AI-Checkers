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
    bool terminal = false;
    // the move which this node represents
    Move* move;
    // the successors of this node
    std::vector<Node*>* successors = nullptr;
    // the board state of this node
    Board* boardState = nullptr;

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
     * @param move the move to start from
     * @return the head of the node tree
     */
    static Node *createTree(Board *bs, int depth, Move *move);

    /**
     * traverses an existing tree to append nodes the the end of that tree
     * until it is the desired depth
     * @param bs the current board
     * @param depth desired depth
     * @param node the node to start from
     * @return the head of the node tree
     */
     static Node *appendToTree(Board *bs, int depth, Node *node);

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

    /* accessors and mutators */
    std::vector<Node*>* getSuccessors();
    void setMove(Move *move);
    int getValue();
    void setValue(int value);
    bool isTerminal();
    void setTerminal(bool terminal);
    Move* getMove();
    Move* getLastMove();
    Board* getBoardState();
    void setSuccessors(std::vector<Node *> *successors);
};

#endif //MINIMAX_AI_CHECKERS_NODE_H
