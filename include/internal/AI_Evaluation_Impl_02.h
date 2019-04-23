//
// Created by Luke McNamee on 2019-03-21.
//

#ifndef MINIMAX_AI_CHECKERS_02_AI_MINIMAX_02_H
#define MINIMAX_AI_CHECKERS_02_AI_MINIMAX_02_H

#include "AI.h"
#include "Move.h"

/**
 * A definition of evaluateBoardState
 */
class AI_Minimax_02 : public AI {

public:
    /* constructor */
    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead
     */
    AI_Minimax_02(int lookAhead, Color color, bool usePruning)
        : AI(lookAhead, color, "KingMe v1", usePruning) {};

private:
    /* methods */
    /**
     * an evaluation function where the location of a non king piece longitudinally
     * across the board effects the value
     * @param node the node to evaluate
     * @return the numerical value of the board state
     */
    int evaluateBoardState(Board *boardState) override;
};

#endif //MINIMAX_AI_CHECKERS_02_AI_MINIMAX_02_H
