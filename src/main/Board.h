//
// This class represents the board by holding the 24 pieces in a 2d-array
//
// Created by Luke on 1/28/2019.
//

#ifndef CHECKERS_01_BOARD_H
#define CHECKERS_01_BOARD_H

#include <vector>
#include <set>
#include "POCO/Checker.h"
#include "POCO/Move.h"

class Board {
private:
    const std::string PLAYER_ONE_COLOR = "Red";
    const std::string PLAYER_TWO_COLOR = "White";
    Color turn = RED;
    // Data structure representing the board
    Checker* grid[8][8] = {nullptr};
    std::vector<std::vector<Checker*>>* boardGrid = new std::vector<std::vector<Checker*>>();
    std::vector<Move*>* movesToDelete = new std::vector<Move*>();
    Move* lastMove = nullptr;
    // player2 and player1 pieces on the board
    std::vector<Checker*>* redPieces = new std::vector<Checker*>();
    std::vector<Checker*>* whitePieces = new std::vector<Checker*>();
    std::string getColorStr(Color);
    void setLastMove(Move* lastMove);
public:
    /**
     * Constructs a board with pieces ready for play
     */
    Board();
    Color getTurn();
    void setTurn(Color color);
    Board(std::vector<Checker *> *startState, Color turn);

    Move* getLastMove();

    /**
     * @return a vector containing pointers to the red checkers still in play
     */
    std::vector<Checker*>* getRedPieces();

    /**
     * @return a vector containing pointers to the black checkers still in play
     */
    std::vector<Checker*>* getWhitePieces();

    /**
     * Returns the piece at the space at the row and column indicated by parameters. Does not check if there is
     * a piece at the space
     * @param row
     * @param col
     * @return a pointer to the checker at the space requested
     */
    Checker* getAt(int row, int col);

    /**
     * Returns true if there is a piece at the ath row nth and column
     * @param row
     * @param col
     * @return true if there is a piece at the space
     */
    bool contains(int row, int col);

    /**
     * moves a piece from one row and column to another
     * @param move
     */
    void move(Move *move, bool dontClear, bool changeTurn);

    /**
     * Print the board to terminal
     */
    void printBoard();

    int getRedCount();
    int getWhiteCount();

    void removePiece(Checker* c);

    Board *copy();
};


#endif //CHECKERS_01_BOARD_H
