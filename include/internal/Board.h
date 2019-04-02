//
// Created by Luke on 1/28/2019.
//

#ifndef MINIMAX_AI_CHECKERS_BOARD_H
#define MINIMAX_AI_CHECKERS_BOARD_H

#include <vector>
#include <set>
#include "Checker.h"
#include "Move.h"

/**
 * This class represents the board by holding the 24 pieces in a 2d-array
 */
class Board {
private:
    /* field vars */
    const std::string PLAYER_ONE_COLOR = "Red";
    const std::string PLAYER_TWO_COLOR = "White";
    Color turn = RED;
    // Data structure representing the board
    Checker* grid[8][8] = {{nullptr}};
    Move* lastMove = nullptr;
    // player2 and player1 pieces on the board
    std::vector<Checker*>* redPieces = new std::vector<Checker*>();
    std::vector<Checker*>* whitePieces = new std::vector<Checker*>();
    bool gameOver = false;
    const static int BOARDHEIGHT = 8;
    const static int BOARDWIDTH = 8;
public:
    /* constructors, destructor, and copy */
    /**
    * Constructs a board with pieces ready for play at starting configuration
    */
    Board();

    /**
    * Constructs a board with pieces ready for play at any configuration given
    */
    Board(std::vector<Checker *> *startState, Color turn);

    /**
     * destroys the board and deletes all fields
     */
    ~Board();

    /**
     * returns a pointer to a copy of this object
     * @return a copy of this
     */
    Board *copy();

    /* util functions  */

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
     * @param move the pointer to the move to implement
     * @param changeTurn indicates wheather the turn should change
     */
    void move(Move *move, bool changeTurn);

    /**
     * Print the board to terminal
     */
    void printBoard();

    /**
     * removes a piece from the board and from all containers within
     * @param c the checker to be removed
     */
    void removePiece(Checker* c);


    /* accessors and mutators */
    bool isGameOver() const;
    void setGameOver(bool gameOver);
    static const int getBOARDHEIGHT();
    static const int getBOARDWIDTH();
    Color getTurn();
    void setTurn(Color color);
    Move* getLastMove();
    int getRedCount();
    int getWhiteCount();
    /**
     * @return a vector containing pointers to the red checkers still in play
     */
    std::vector<Checker*>* getRedPieces();
    /**
     * @return a vector containing pointers to the black checkers still in play
     */
    std::vector<Checker*>* getWhitePieces();
};


#endif //MINIMAX_AI_CHECKERS_BOARD_H
