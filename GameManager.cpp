//
// Created by Luke on 1/29/2019.
//

#include <iostream>
#include "GameManager.h"
#include "Rules.h"

GameManager::GameManager(Board* board, Rules* rules,
                         Player* black, Player* red) {
    this->board = board;
    this->rules = rules;
    this->black = black;
    this->red = red;

    play();
}

void GameManager::play() {
    Move* currentMove;
    while(!gameOver) {

        // while the move is not valid ask for a new move
        bool validMove = false;
        while (!validMove) {
            // first print the board
            board->printBoard();

            // call getMove to request the next move from the current player
            currentMove = getMove();

            // check if the move is valid
            validMove = rules->legalMove(currentMove, curTurn);


            Move* chainMe = currentMove;
            while(rules->ca(chainMe)) {

            }
        }
        // check if the move is a 'kingme' move and if so then king the piece
        kingMe(currentMove);


        // when we have a valid move push the move to the board
        board->move(currentMove);

        // Change the turn
        curTurn = (curTurn == 'b') ? 'r' : 'b';

        // check if the game is over
         if(board->getRedCount() == 0 || board->getBlackCount() == 0)
             gameOver = true;
    }
    std::cout << ((board->getBlackCount() == 0) ? "Black wins" : "Red wins");

    delete currentMove;
}

Move *GameManager::getMove() {
    Move* currentMove;
    switch (curTurn) {
        case 'b':
            currentMove = black->getMove();
            break;
        case 'r':
            currentMove = red->getMove();
            break;
        default:
            std::cout << "Error" << std::endl;
    }
    return currentMove;
}

void GameManager::kingMe(Move *move) {
    if((move->getDestRow() == 7 && move->getColor() == 'r') ||
       (move->getDestRow() == 0 && move->getColor() == 'k'))
        move->setKingMove(true);
}
