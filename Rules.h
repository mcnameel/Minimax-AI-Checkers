//
// This class is used as a rulebook for the game.
//
// Created by Luke on 1/31/2019.
//

#ifndef CHECKERS_01_RULES_H
#define CHECKERS_01_RULES_H


#include <vector>
#include <set>
#include "Move.h"
#include "Board.h"

class Rules {
public:
    /* functions */
    /**
     * Initializes a rules object, board cannot be null
     * @param board
     */
    Rules(Board *board);

    /**
     * checks if the move is a legal move
     * @param move
     * @return true if the move is legal
     */
    bool legalMove(Move* move, char turn);

    /**
     * Checks if a move is legal
     * @param move
     * @return true if the move can be completed
     */
    bool validCapture(Move *move);

    /** !Not functioning
     * Checks if the player is required to chain jump from the destination
     * space. If so it calls move->setCanChain()
     * @param move
     * @return true if another move is required
     */
    bool canChain(Move* move);

    /** !Not being used, might remove
     * Checks if the player is moving his/her/its own piece
     * @param move
     * @return true if the player is moving the correct color
     */
    bool validPlayer(Move* move, char curTurn);

    /**
     * Checks if the piece a the given space needs to capture
     * @param curRow
     * @param curCol
     * @param color
     * @return true if the piece must capture
     */
    bool mustCapture(int curRow, int curCol, char color);

    /**
      * Gets the captures the player is required to make. If there are no
      * captures the set will be empty
      * @param color the player whose turn it is
      * @return pointer to a set of pointers to moves
      */
    std::set<Move*>* requiredCaptures(char color);

    /**
     * Checks if a single piece can capture
     * @param c
     * @param isBlack
     * @param captures the set of captures which will be added to if a capture
     *  is possible
     * @return true if there are possible captures to make
     */
    bool checkCaptures(Checker* c, std::set<Move*>* captures);
private:
    /* vars */
    Board* board;

    // set all the spaces to default to false and then change them in the
    // constructors
    bool playableSpaces[8][8] = {false};

    /**
     * Checks if the given move is a capture and if it is set the capture
     * space of the move
     * @param m
     * @return true if the move is a capture
     */
    bool isCapture(Move* m);

    /**
     * Checks if the space is on a black square (aka a playable space) and if
     * the space is unoccupied
     * @param row
     * @param col
     * @return true if valid move
     */
    bool validSpace(int row, int col);

    bool checkUpMoves(Checker* c, std::set<Move*>* captures);
    bool checkDownMoves(Checker* c, std::set<Move*>* captures);
};

#endif //CHECKERS_01_RULES_H
