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
    /**
     * Check if a piece should be crowned and then kings the move
     * @param move
     * @param boardState
     * @return true if the move is a king move
     */
    static bool crownMe(Move *move, Board *boardState);

    /**
     * checks if the move is a legal move
     * @param move
     * @return true if the move is legal
     */
    static bool legalMoveFromColor(Move *move, Board *boardState);

    /**
     * checks if a move is legal by comparing the passed in move to all the
     * possible moves this turn
     * @param move the move to check
     * @param boardState the board state when the move will be made
     * @return true if the move is legal
     */
    static bool legalMove(Move *move, Board *boardState);

    /**
     * Checks if a move is legal
     * @param move
     * @return true if the move can be completed
     */
    static bool validCapture(Move *move, Board* boardState);

    /**
     * combine two vectors
     */
    static std::vector<Move*> *combine(std::vector<Move*>* vec1, std::vector<Move*>* vec2);

    /**
     * Returns all the legal jumps for a piece at the given location
     * @param isBlack signifies which player's turn it is
     * @param row the row of the piece
     * @param col the column of the piece
     * @return A vector of all the possible moves
     */
    static std::vector<Move*> *getAllJumpsAtPos(Board *boardState, Checker *checker);

    /**
     * returns all legal moves that can be made this turn
     * @param boardState the current board
     * @return collection of all legal moves this turn
     */
    static std::vector<Move*> *getAllLegalMoves(Board* boardState);

    /**
     * get all the jumps that a player can make this turn
     * @param boardState the current board
     * @return all jumps that a player can make this turn
     */
    static std::vector<Move*> *getAllJumpsForPlayer(Board *boardState);

private:
    /* vars */
    // set all the spaces to default to false and then change them in the
    static bool playableSpaces[8][8];

    /* functions */
    /**
     * get all moves for a given piece
     * @param checker the piece to get the moves from
     * @param boardState the current board
     * @return all moves this piece can make
     */
    static std::vector<Move*> *getMovesAtPos(Checker *checker, Board *boardState);

    /**
     * checks if a move is going in a legal direction for the color
     * @param move the move to check
     * @param boardState the current board
     * @return true if the direction is legal
     */
    static bool legalDirection(Move *move, Board *boardState);

    /**
     * getDownLeftJumps
     * get the jump which can be made in current row -2, column -2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move *getLLJump(Checker *c, Board *boardState);

    /**
     * getDownRightJumps
     * get the jump which can be made in current row -2, column +2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move *getLRJump(Checker *c, Board* boardState);

    /**
     * get the which can be made in current row +2, column -2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move *getULJump(Checker *c, Board *boardState);

    /**
     * getUpperRightJump
     * get the jump which can be made in current row +2, column +2
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if the jump is valid otherwise nullptr
     */
    static Move *getURJump(Checker *c, Board* boardState);

    /**
    * getDownLeftMove
    * get the Move which can be made in current row -1, column -1
    * @param row
    * @param col
    * @param boardState
    * @return a pointer to the move if the Move is valid otherwise nullptr
    */
    static Move *getLLMove(Checker *c, Board *boardState);

    /**
     * getDownRightMove
     * get the jump which can be made in current row -1, column +1
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move, if valid, otherwise nullptr
     */
    static Move *getLRMove(Checker *c, Board* boardState);

    /**
     * getUpperLeftMove
     * get the Move which can be made in current row +1, column -1
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if valid otherwise nullptr
     */
    static Move *getULMove(Checker *c, Board *boardState);

    /**
     * getUpperRightMove
     * get the Move which can be made in current row +1, column +1
     * @param row
     * @param col
     * @param boardState
     * @return a pointer to the move if valid otherwise nullptr
     */
    static Move *getURMove(Checker *c, Board* boardState);

    /**
     * Returns all the legal jumps for a piece at the given location
     * @param isBlack signifies which player's turn it is
     * @param row the row of the piece
     * @param col the column of the piece
     * @return A vector of all the possible moves
     */
    static std::vector<Move*> *getJumpsAtPos(Board *boardState, Checker *checker);

    /**
     * Checks if the given move is a capture and if it is set the capture
     * space of the move
     * @param m
     * @return true if the move is a capture
     */
    static bool isCapture(Move *m);

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
