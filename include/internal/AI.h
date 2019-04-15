//
// Created by Luke McNamee on 2019-03-21.
//

#ifndef MINIMAX_AI_CHECKERS_02_AI_H
#define MINIMAX_AI_CHECKERS_02_AI_H

#include <random>
#include "Player.h"
#include "Move.h"
#include "Node.h"

/**
 * This class is an AI redefining player which will use minimax with alpha
 * beta pruning to find the best method. This class cannot be initialized
 * because the pure virtual method evaluateBoardState must be defined
 */
class AI : public Player {

public:
    /**
     * Uses minimax with alpha beta pruning to find the best move. This class
     * must be extended and a definition for the evaluation algorithm must be
     * provided
     * @param boardState the current board
     * @return the best move to make
     */
    Move *getMove(Board *boardState) override;
private:
    /* field vars */
    // The board state from the last time this player moved
    Board *lastBoard = nullptr;

protected:
    /* field vars */
    // pseudo positive and negitive infinity
    static const int MAX = 2147483647;
    static const int MIN = -2147483647;
    // the number of moves to look down head on each move
    int lookAhead;
    // the node tree to be saved in between turns to prevent the recreation of
    // the same derivations
    Node *currentTree = nullptr;

    /* constructor and destructor */
    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead.
     *        MUST BE LARGER THAN 1!
     * @param color the color of the player.
     * @param name the name of the evaluation function
     */
    AI(int lookAhead, Color color, std::string name);

    /**
     * destroy all fields of this class
     */
    ~AI() override;

    /* virtual functions */
    /**
     * The evaluation algorithm which minimax will use. Gives a specific board
     * a numerical value based on how desirable it is.
     * @param boardState the board to evaluate
     * @return a numerical value of the board state
     */
    virtual int evaluateBoardState(Board *boardState) = 0;

    /* methods */
    /**
     * Minimax with alpha beta pruning. Alternate between the maximizing and
     * minimizing players moves through a tree of nodes to return the most
     * favorable move to make assuming the opponent also makes the best moves
     * @param node node at the head of the tree
     * @param depth the depth in the tree to pursue
     * @param maximizingPlayer a boolean which should be true when called
     * @param alpha the alpha cut off value, when called this should be
     *        -infinity
     * @param beta the alpha cut off value, when called this should be
     *        +infinity
     * @return the value of the best node to choose which will be found in the
     *        successors of the head
     */
    int minimaxAB(Node *node, int depth, bool maximizingPlayer, int alpha, int beta);

    /**
     * Creates a tree with the given board state
     * @param bs the current board state
     * @return the node at the head of the tree
     */
    Node *makeTree(Board *bs);

    /**
     * calls a method in Node which finds the node representing the last turn
     * taken and removes that from the successors of deleteMe, then deletes
     * deleteMe and all successors recursively. Then returns the move which
     * was removed.
     * @param boardState the current board state
     * @param deleteMe the node to be deleted
     * @return the node represents the last move from boardState
     */
    Node* deleteOldNodes(Board *boardState, Node *deleteMe);

    /**
     * generates a pseudo-random number
     * @param low the low bound of the random value
     * @param high the high bound of the random value
     * @return the random int
     */
    static int random(int low, int high);

    /**
     * compares two values and returns the maximum
     * @param val1
     * @param val2
     * @return the maximum of the two values
     */
    int max(int val1, int val2);

    /**
     * compares two values and returns the minimum
     * @param val1
     * @param val2
     * @return the minimum of the two values
     */
    int min(int val1, int val2);
};
#endif //MINIMAX_AI_CHECKERS_02_AI_H