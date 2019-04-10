//
// Created by Luke McNamee on 2019-03-24.
//

#ifndef MINIMAX_AI_CHECKERS_02_AI_MINIMAX_03_H
#define MINIMAX_AI_CHECKERS_02_AI_MINIMAX_03_H


#include "Node.h"
#include "AI.h"

/**
 * A definition of evaluateBoardState
 */
class AI_Minimax_03 : public AI {

public:
    /* constructor */
    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead
     */
    AI_Minimax_03(int lookAhead, Color color) : AI(lookAhead, color) {};

private:
    /* methods */
    /**
     * an evaluation function where the location of a non king piece
     * longitudinally across the board effects the value. This is more improved
     * from the last one
     * @param node the node to evaluate
     * @return the numerical value of the board state
     */
    int evaluateBoardState(Node *node) override;
};

#endif //MINIMAX_AI_CHECKERS_02_AI_MINIMAX_03_H
