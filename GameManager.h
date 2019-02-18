//
// This class controls the flow of control on the game and interacts with the
// players to request a move then checks if the move is legal, using the Rules
// class, and then passes the move to the board object to be implemented
//
// Created by Luke on 1/29/2019.
//

#ifndef CHECKERS_01_GAMEMANAGER_H
#define CHECKERS_01_GAMEMANAGER_H


#include "Board.h"
#include "Player.h"
#include "Rules.h"

class GameManager {
public:
    /**
     * Initializes a GameManager object
     * @param board
     * @param rules
     * @param red
     * @param black
     */
    GameManager(Board* board, Rules* rules, Player* red, Player* black);

private:

    /* vars */
    bool gameOver = false;
    Board* board;
    Rules* rules;
    Player* red;
    Player* black;
    // current turn starts with black by default
    char curTurn = 'b';

    /* functions */
    /**
     * Gets the next move from the player whose turn it is
     * @return pointer to a move object
     */
    Move* getMove();

    void play();

    void kingMe(Move *move);
};


#endif //CHECKERS_01_GAMEMANAGER_H
