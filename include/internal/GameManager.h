//
// Created by Luke on 1/29/2019.
//

#ifndef MINIMAX_AI_CHECKERS_GAMEMANAGER_H
#define MINIMAX_AI_CHECKERS_GAMEMANAGER_H


#include "Board.h"
#include "Player.h"
#include "Rules.h"

/**
 * This class controls the flow of control on the game and interacts with the
 * players to request a move then checks if the move is legal, using the Rules
 * class, and then passes the move to the board object to be implemented
 */
class GameManager {
public:
    /* constructor and destructor */
    /**
     * Initializes a GameManager object
     * @param board
     * @param rules
     * @param player1 A pointer to a implementation of the player class
     * @param player2 A pointer to a implementation of the player class
     */
    GameManager(Board* board, Player* player1, Player* player2);

    ~GameManager();

    /**
     * After initialization this begins the game
     * @returns color of the winner: either RED, WHITE, or NEITHER
     */
    Color play();
    int turnCount = 0;
private:
    /* field vars */
    Board* board;
    Player* player1;
    Player* player2;
    //int turnCount = 0;

    /* functions */
    /**
     * Gets the next move from the player whose turn it is
     * @return pointer to a move object
     */
    Move* getMove(Board *bs);

    void takeTurn();

    /**
     * gets a legal move by calling the rules
     * @return the next move to be pushed to the board
     */
    Move* getLegalMove();

    /* util functions */
    /**
     * returns true if the game is a draw
     * @param bs current boardState
     * @param pieceCountDraw the piece count after which to start looking for
     *      a draw
     * @param turnsWithoutProfit number of turns which the board has not changed state
     * @return
     */
    bool isDraw(Board *bs, int *pieceCountDraw, int *turnsWithoutProfit);

    /**
     * Check if a piece should be crowned and if so crowns the piece object
     * @param move the piece to check
     * @return true if the piece has been crowned
     */
    bool crownMe(Move *move);
};


#endif //MINIMAX_AI_CHECKERS_GAMEMANAGER_H
