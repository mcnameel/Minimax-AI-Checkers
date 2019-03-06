//
// This class is used as a rulebook for the game. All functions are static and
// can be called at any time as long as the game state is passed through params
//
// Created by Luke on 1/31/2019.
//

#ifndef CHECKERS_01_RULES_H
#define CHECKERS_01_RULES_H


#include <vector>
#include <set>
#include "POCO/Move.h"
#include "Board.h"
#include "misc/Player.h"

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
    static Move* turn(Board* board, Player* player);

    static bool legalMultiCapture(Move* lastMove, Move* newMove,  Board* boardState);
    /**
     * Checks if a move is legal
     * @param move
     * @return true if the move can be completed
     */
    static bool validCapture(Move *move, Board* boardState);

    /** !Not functioning
     * Checks if the player is required to chain jump from the destination
     * space. If so it calls move->setCanChain()
     * @param move
     * @return true if another move is required
     */
    static bool canChain(Move* move, Board* boardState);

    /** !Not being used, might remove
     * Checks if the player is moving his/her/its own piece
     * @param move
     * @return true if the player is moving the correct color
     */
    static bool validPlayer(Move* move, Board* boardState);

    /**
     * Checks if the piece a the given space needs to capture
     * @param curRow
     * @param curCol
     * @param color
     * @return true if the piece must capture
     */
    static bool mustCapture(int curRow, int curCol, Board* boardState);

    /**
      * Gets the captures the player is required to make. If there are no
      * captures the set will be empty
      * @param color the player whose turn it is
      * @return pointer to a set of pointers to moves
      */
    static std::set<Move*>* requiredCaptures(Board* boardState);

    /**
     * Checks if a single piece can capture
     * @param c
     * @param isBlack
     * @param captures the set of captures which will be added to if a capture
     *  is possible
     * @return true if there are possible captures to make
     */
    static bool checkCaptures(Checker* c, std::vector<Move*>* captures, Board* boardState);

    static std::vector<Move *> *getDownJumps(int row, int col, Board *boardState);

    static std::vector<Move*>* getUpJumps(int row, int col, Board* boardState);
    static std::vector<Move*>* combine(std::vector<Move*>* vec1, std::vector<Move*>* vec2);
        /**
         * Returns all the legal jumps for a piece at the given location
         * @param isBlack signifies which player's turn it is
         * @param row the row of the piece
         * @param col the column of the piece
         * @return A vector of all the possible moves
         */
         static std::vector<Move *> *getJumpsAtPos(Board *boardState, Checker *checker);


    /**
     * get all the jumps for a given player
     * @param color the color of the player
     * @return a vector of all jumps a player can make
     */
    static std::vector<Move*>* getJumps(Board* boardState);

    static bool validMultiCapture(Move* move, Board* boardState);
    static bool requiredMultiCapture(Move *move, Board *boardState, bool isKing);
    static std::vector<Move*>* getAllLegalMoves(Board* boardState);

private:
    static int numRequiredCaps(Move* m, Board* boardState);
    //Board* board;
    // set all the spaces to default to false and then change them in the
    // constructors
    static bool playableSpaces[8][8];
    static std::vector<Move*>* copy(std::vector<Move*>* vector);
    /* vars */
    static bool validMove(Move* move, Board* boardState);
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

    static bool checkUpMoves(Checker* c, std::set<Move*>* captures, Board* boardState);
    static bool checkDownMoves(Checker* c, std::set<Move*>* captures);
};

#endif //CHECKERS_01_RULES_H
