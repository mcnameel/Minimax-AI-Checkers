//
// Created by Luke McNamee on 2019-04-15.
//

#ifndef MINIMAX_AI_CHECKERS_02_AI_EVALUATION_IMPL_07_H
#define MINIMAX_AI_CHECKERS_02_AI_EVALUATION_IMPL_07_H


#include "Node.h"
#include "AI.h"

/**
 * A definition of evaluateBoardState
 */
class AI_Minimax_07 : public AI {

public:
    /* constructor */
    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead
     */
    AI_Minimax_07(int lookAhead, Color color) : AI(lookAhead, color, "Horizon Peek v2") {};

private:
    /* methods */
    /**
     * an evaluation function where the location of a non king piece
     * longitudinally across the board effects the value. This is more improved
     * from the last one
     * @param node the node to evaluate
     * @return the numerical value of the board state
     */
    int evaluateBoardState(Board *boardState) override;

    /**
     * the evaluation function for the early and mid game which uses the
     * values kings as 22 points and men as 6 points + the distance across the
     * board then subtracts this value by the same value for the opponents
     * pieces
     * @param boardState the board representation
     * @return a heuristic evaluation of the board
     */
    int earlyGameEval(Board *boardState, std::vector<Checker*> *willBeCaptured);

    /**
     * the evaluation function for the endgame which uses the earlyGameEval
     * function and then also sums the distance between this players king
     * pieces and the opponent's kings. The lower the distance the better.
     * @param boardState the board representation
     * @return a heuristic evaluation of the board
     */
    int endGameEval(std::vector<Checker *> *myPcs,
                    std::vector<Checker *> *otherPcs,
                    std::vector<Checker *> *willBeCaptured);

    std::vector<Checker *> *getCapturedPieces(Board *pBoard);
};


#endif //MINIMAX_AI_CHECKERS_02_AI_EVALUATION_IMPL_07_H
