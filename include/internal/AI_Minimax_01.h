//
// Created by Luke on 2/8/2019.
//

#ifndef MINIMAX_AI_CHECKERS_AI_H
#define MINIMAX_AI_CHECKERS_AI_H


#include "Move.h"
#include "Node.h"
#include "Player.h"
#include "AI.h"

/**
 * A definition of evaluateBoardState
 */
class AI_Minimax_01 : public AI {

public:
    /* constructor */
    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead
     */
    AI_Minimax_01(int lookAhead, Color color) : AI(lookAhead, color) {};

private:
    /* destructor */
    ~AI_Minimax_01() override {
        delete currentTree;
    };

    /* methods */
    /**
     * a simple evaluation function where a non king piece is valued as 1 and
     * a king piece is valued at 3
     * @param node the node to evaluate
     * @return the numerical value of the board state
     */
    int evaluateBoardState(Node *node) override;
};


#endif //MINIMAX_AI_CHECKERS_AI_H
