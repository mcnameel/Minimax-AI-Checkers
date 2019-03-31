//
// Created by Luke on 1/31/2019.
//

#ifndef MINIMAX_AI_CHECKERS_RULES_H
#define MINIMAX_AI_CHECKERS_RULES_H


#include <vector>
#include <set>
#include "Move.h"
#include "Board.h"
#include "Player.h"
/**
 * This class is used as a rulebook for the game. All functions are static and
 * can be called at any time as long as the game state is passed through params
 */
class Rules {
public:
    /* functions */

    static bool crownMe(Move *move);
    /**
     * checks if the move is a legal move
     * @param move
     * @return true if the move is legal
     */
    static bool legalMoveFromColor(Move *move, Board *boardState);
    static bool legalMove(Move *move, Board *boardState);
    static bool shouldCrown(Move *move);
    /**
     * Checks if a move is legal
     * @param move
     * @return true if the move can be completed
     */
    static bool validCapture(Move *move, Board* boardState);

    /**
     * get all jumps which can be made in current row -2
     * @param row
     * @param col
     * @param boardState
     * @return vector of jumps which can be made
     */
    static std::vector<Move *> *getDownJumps(int row, int col, Board *boardState);

    /**
     * get all jumps which can be made in current row +2
     * @param row
     * @param col
     * @param boardState
     * @return vector of jumps which can be made
     */
    static std::vector<Move*>* getUpJumps(int row, int col, Board* boardState);

    /**
     * getDownLeftJumps
     * get the jump which can be made in current row -2, column -2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move *getDLJump(int row, int col, Board *boardState);

    /**
     * getDownRightJumps
     * get the jump which can be made in current row -2, column +2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move* getDRJump(int row, int col, Board* boardState);

    /**
     * get the which can be made in current row +2, column -2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move *getULJump(int row, int col, Board *boardState);

    /**
     * getUpperRightJump
     * get the jump which can be made in current row +2, column +2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move* getURJump(int row, int col, Board* boardState);

    /**
     * combine two vectors
     */
    static std::vector<Move*>* combine(std::vector<Move*>* vec1, std::vector<Move*>* vec2);

    /**
     * Returns all the legal jumps for a piece at the given location
     * @param isBlack signifies which player's turn it is
     * @param row the row of the piece
     * @param col the column of the piece
     * @return A vector of all the possible moves
     */
     static std::vector<Move *> *getJumpsAtPos(Board *boardState, Checker *checker);

    static bool validMultiCapture(Move* move, Board* boardState);
    static bool requiredMultiCapture(Move *move, Board *boardState, bool isKing);
    static std::vector<Move*>* getAllLegalMoves(Board* boardState);

private:
    // set all the spaces to default to false and then change them in the
    // constructors
    static bool playableSpaces[8][8];
    static std::vector<Move*>* copy(std::vector<Move*>* vector);
    /* vars */
    static std::vector<Move*>* getDownMoves(int row, int col, Board* boardState);
    static std::vector<Move *>* getUpMoves(int row, int col, Board* boardState);
    static std::vector<Move*>* getMovesAtPos(int row, int col, Board* boardState);
    static bool legalDirection(Move* move, Board* boardState);

    /**
     * Checks if the given move is a capture and if it is set the capture
     * space of the move
     * @param m
     * @return true if the move is a capture
     */
    static bool isCapture(Move* m);

    /**
     * Checks if the space is on a black square (aka a playable space) and if
     * the space is unoccupied
     * @param row
     * @param col
     * @return true if valid move
     */
    static bool validSpace(int row, int col, Board* boardState);
};

#endif //MINIMAX_AI_CHECKERS_RULES_H
